/*
  ==============================================================================

    AudioVisualizerController.h
    Created: 17 Sep 2017 5:41:09pm
    Author:  Jack Campbell

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"

//==============================================================================
/*
*/



class AudioVisualizerController    : public Component
{
public:
    //AudioVisualizerController();
    AudioVisualizerController(int width, int height);
    ~AudioVisualizerController();

    void paint (Graphics&) override;
    void resized() override;
    void change(ChangeBroadcaster* source);

protected:
    

    AudioThumbnailCache thumbnailCache;                  // [1]
    AudioThumbnail thumbnail;                            // [2]
    AudioFormatManager formatManager;
    
    void transportSourceChanged();
    void thumbnailChanged();
    
    
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (AudioVisualizerController)
};
