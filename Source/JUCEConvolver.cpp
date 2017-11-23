/*
  ==============================================================================

    JUCEConvolver.cpp
    Created: 23 Nov 2017 4:21:00pm
    Author:  Jack Campbell

  ==============================================================================
*/

#include "JUCEConvolver.h"
// big six
JUCEConvolver::JUCEConvolver() : _convolver()
{}

JUCEConvolver::~JUCEConvolver()
{}

// interface
void JUCEConvolver::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    dsp::ProcessSpec spec {sampleRate, static_cast<uint32>(samplesPerBlock), 2};
    this->_convolver.prepare(spec);
}

void JUCEConvolver::setImpulseResponse(File ir)
{
    this->_convolver.loadImpulseResponse(ir, true, true, ir.getSize());
}

void JUCEConvolver::process(dsp::AudioBlock<float> block)
{
    this->_convolver.process(dsp::ProcessContextReplacing<float>(block));
}

void JUCEConvolver::reset()
{
    this->_convolver.reset();
}
