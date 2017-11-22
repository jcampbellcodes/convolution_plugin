/*
  ==============================================================================

    InputVisualizer.cpp
    Created: 17 Nov 2017 10:16:48am
    Author:  Jack Campbell

  ==============================================================================
*/

#include "ImpulseVisualizer.h"

ImpulseVisualizer::ImpulseVisualizer(int width, int height) : AudioVisualizerController(width, height) {};

// input just sets the impulse response file and visualizes
void ImpulseVisualizer::setThumbnail (InputSource* src)
{
    //AudioPlayer::setImpulseFile(file);
    thumbnail.setSource (src);          // [7]
    
}
