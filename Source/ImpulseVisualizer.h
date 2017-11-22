/*
  ==============================================================================

    AudioVisualizerController.h
    Created: 17 Sep 2017 5:41:09pm
    Author:  Jack Campbell

  ==============================================================================
*/

#pragma once

#include "./AudioVisualizerController.h"

//==============================================================================
/*
*/



class ImpulseVisualizer    : public AudioVisualizerController
{
public:
    //AudioVisualizerController();
    ImpulseVisualizer(int width, int height);
    void setThumbnail (InputSource* src);
private:
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (ImpulseVisualizer)
};
