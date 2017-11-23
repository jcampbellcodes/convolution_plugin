/*
  ==============================================================================

    CustomConvolver.h
    Created: 23 Nov 2017 4:20:49pm
    Author:  Jack Campbell

  ==============================================================================
*/

#pragma once
#include "Convolver.h"

class CustomConvolver : public Convolver
{
public:
    // big six
    CustomConvolver();
    ~CustomConvolver();
    
    // interface
    void prepareToPlay (double sampleRate, int samplesPerBlock) override final;
    void setImpulseResponse(File ir) override final;
    void process(dsp::AudioBlock<float> block) override final;
    void reset() override final;
};
