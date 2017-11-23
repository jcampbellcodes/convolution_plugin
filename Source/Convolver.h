/*
  ==============================================================================

    Convolver.h
    Created: 23 Nov 2017 2:16:53pm
    Author:  Jack Campbell
    Abstract class for strategy
  ==============================================================================
*/

#pragma once
#include "../JuceLibraryCode/JuceHeader.h"

class Convolver
{
    public:
    // big four
    Convolver() = default;
    Convolver(const Convolver&) = delete;
    Convolver& operator=(const Convolver&) = delete;
    Convolver(const Convolver&&) = delete;
    Convolver& operator=(const Convolver&&) = delete;
    virtual ~Convolver() = default;
    
    // interface
    virtual void prepareToPlay (double sampleRate, int samplesPerBlock) = 0;
    virtual void setImpulseResponse(File ir) = 0;
    virtual void process(dsp::AudioBlock<float> block) = 0;
    virtual void reset() = 0;
};
