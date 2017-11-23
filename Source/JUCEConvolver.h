/*
  ==============================================================================

    JUCEConvolver.h
    Created: 23 Nov 2017 4:21:00pm
    Author:  Jack Campbell

  ==============================================================================
*/

#pragma once
#include "Convolver.h"

class JUCEConvolver : public Convolver
{
public:
    // big six
    JUCEConvolver();
    ~JUCEConvolver();
    
    // interface
    void prepareToPlay (double sampleRate, int samplesPerBlock) override final;
    void setImpulseResponse(File ir) override final;
    void process(dsp::AudioBlock<float> block) override final;
    void reset() override final;
    
private:
    dsp::Convolution _convolver;
};
