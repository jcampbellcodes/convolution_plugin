/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"
#include "PluginProcessor.h"
#include "./ImpulseVisualizer.h"

//==============================================================================
/**
*/
class ConvolutionReverbAudioProcessorEditor  :  public AudioProcessorEditor,
                                                public ComboBox::Listener,
                                                public Slider::Listener,
                                                public FileDragAndDropTarget,
                                                public ChangeListener
{
public:
    ConvolutionReverbAudioProcessorEditor (ConvolutionReverbAudioProcessor&);
    ~ConvolutionReverbAudioProcessorEditor();

    //==============================================================================
    void paint (Graphics&) override;
    void resized() override;
    void comboBoxChanged (ComboBox* comboBoxThatHasChanged) override;
    void sliderValueChanged (Slider* sliderThatWasMoved) override;
    
    virtual bool 	isInterestedInFileDrag (const StringArray &files) override;
    virtual void 	filesDropped (const StringArray &files, int x, int y) override;
    void changeListenerCallback (ChangeBroadcaster* source) override;

private:
    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    ConvolutionReverbAudioProcessor& processor;
    
    std::unique_ptr<ComboBox> comboBox;
    std::unique_ptr<Label> label2;
    std::unique_ptr<ImpulseVisualizer> impulse_response;
    std::unique_ptr<Label> knoblabel;
    std::unique_ptr<Slider> balance_knob;
    std::unique_ptr<Label> srtverb;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (ConvolutionReverbAudioProcessorEditor)
};
