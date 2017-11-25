/*
 ==============================================================================
 
 CustomConvolver.cpp
 Created: 23 Nov 2017 4:21:00pm
 Author:  Jack Campbell
 
 ==============================================================================
 */

#include "CustomConvolver.h"
#include <math.h>
// big six
CustomConvolver::CustomConvolver() : _sampleRate(0), _samplesPerBlock(0), fft(nullptr)
{
    formatManager.registerBasicFormats();
}

CustomConvolver::~CustomConvolver()
{
    this->fft.release();
}

// interface
void CustomConvolver::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    this->_sampleRate = sampleRate;
    this->_samplesPerBlock = samplesPerBlock;
    int L = samplesPerBlock * 2;
    this->_fftOrder = (int(log2(L - 1)+1));
    this->_fftTaps = pow(2, _fftOrder);
    
    // fill olap with zeros; mono
    AudioBuffer<float>* buff = new AudioBuffer<float>(1, samplesPerBlock);
    this->_olap = dsp::AudioBlock<float>(*buff);
    this->_olap.fill(0);
    
    buff = new AudioBuffer<float>(1, samplesPerBlock * 2);
    this->_olap = dsp::AudioBlock<float>(*buff);
    this->_olap.fill(0);
    
    this->fft = std::unique_ptr<dsp::FFT>(new dsp::FFT(this->_fftOrder));
    
    buff = new AudioBuffer<float>(1, this->_fftTaps * 2);
    this->accumulationBuffer = dsp::AudioBlock<float>(*buff);
    this->accumulationBuffer.fill(0);
    
    buff = new AudioBuffer<float>(1, this->_fftTaps * 2);
    this->concatenationData = dsp::AudioBlock<float>(*buff);
    this->concatenationData.fill(0);

}

void CustomConvolver::setImpulseResponse(File ir)
{
    // calculate num partitions
    AudioFormatReader* reader = this->formatManager.createReaderFor(ir);
    
    // populate partitions; ie, LRLRLRLR
    this->_numSubfilters = static_cast<int>(reader->lengthInSamples) / this->_samplesPerBlock; // find a more reliable way
                                                                       // to get num IR samples
    dsp::FFT ir_fft(this->_fftOrder);
    
    //get audio buffer h from ir
    
    // allocate an array (size numSubFilters * 2) of arrays
    // each array is size samplesPerBlock * 2
    
    int i = 0;
    while (i < this->_numSubfilters)
    {
        // read time domain audio data
        std::unique_ptr<AudioBuffer<float>> time_domain_audio_chunk(new AudioBuffer<float>(2, this->_fftTaps * 2));
        reader->read(time_domain_audio_chunk.get(),
                     0,
                     this->_samplesPerBlock * 2,
                     i * this->_samplesPerBlock,
                     true,
                     true); // fills up first half with audio data, second half remains zero padding for FFT
        
        // L
        
        float* left = time_domain_audio_chunk->getWritePointer(0);
        
        ir_fft.performRealOnlyForwardTransform(left);
        // R
        float* right = time_domain_audio_chunk->getWritePointer(1);
        ir_fft.performRealOnlyForwardTransform(right);
        //this->fft->performRealOnlyForwardTransform(*time_domain_audio_chunk->getArrayOfWritePointers());
        this->_subfilters.add(dsp::AudioBlock<float>(*time_domain_audio_chunk));
        
        i++;
    }
    
}

void CustomConvolver::process(dsp::AudioBlock<float> block)
{
    if(!this->_subfilters.size()) { return; }
    //force mono
    block = block.getSingleChannelBlock(0);
    
    
    //% input stage -- get L input samples, concatenate to previous L input
    //% samples, get N size DFT
    //% pre-pend the saved overlap to the block
    
    // fill first half of concatenated block with zeros
    dsp::AudioBlock<float> firstHalf = this->concatenationData.getSubBlock(0, this->_samplesPerBlock);
    // add second half of concatenated block to first half
    firstHalf.add(this->concatenationData.getSubBlock(this->_samplesPerBlock - 1, this->_samplesPerBlock));
    // fill second half of concatenated blocks with zeros
    dsp::AudioBlock<float> secondHalf = this->concatenationData.getSubBlock(this->_samplesPerBlock - 1, this->_samplesPerBlock);
    // add "block" to second half
    secondHalf.add(block);
    
    // save olap for next frame
    this->_olap = block;
    
    // get DFT of
    fft->performRealOnlyForwardTransform(this->concatenationData.getChannelPointer(0));
    //% multiplication stage
    
    
    // % multiplication stage, do for each channel:
    //   % create accumulation buffer, size L, all zeros
    this->accumulationBuffer.fill(0);
    
    int iter = 0;
    while(iter < this->_numSubfilters) // TODO --> do we need a frequency delay line to make this baby work?
    {
        // % multiply with the current H_slice
        this->_subfilters[iter].getSingleChannelBlock(0).multiply(this->concatenationData);
        this->_subfilters[iter].getSingleChannelBlock(1).multiply(this->concatenationData);
        // % accumulate with accumulation buffer
        this->accumulationBuffer.getSingleChannelBlock(0).add(this->_subfilters[iter].getSingleChannelBlock(0).multiply(this->concatenationData));
        this->accumulationBuffer.getSingleChannelBlock(1).add(this->_subfilters[iter].getSingleChannelBlock(1).multiply(this->concatenationData));
        iter++;
    }
    
    // inverse transform
    fft->performRealOnlyInverseTransform(this->accumulationBuffer.getChannelPointer(0));
    fft->performRealOnlyInverseTransform(this->accumulationBuffer.getChannelPointer(1));
    block.copy(this->accumulationBuffer.getSubBlock(this->_samplesPerBlock - 1));
}

void CustomConvolver::reset()
{
}
