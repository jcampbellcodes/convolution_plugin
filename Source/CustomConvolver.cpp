/*
 ==============================================================================
 
 CustomConvolver.cpp
 Created: 23 Nov 2017 4:21:00pm
 Author:  Jack Campbell
 
 ==============================================================================
 */

#include "CustomConvolver.h"
// big six
CustomConvolver::CustomConvolver()
{}

CustomConvolver::~CustomConvolver()
{}

// interface
void CustomConvolver::prepareToPlay (double sampleRate, int samplesPerBlock)
{}

void CustomConvolver::setImpulseResponse(File ir)
{}

void CustomConvolver::process(dsp::AudioBlock<float> block)
{}

void CustomConvolver::reset()
{}
