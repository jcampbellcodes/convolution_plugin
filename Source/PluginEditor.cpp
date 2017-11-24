/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"


//==============================================================================
ConvolutionReverbAudioProcessorEditor::ConvolutionReverbAudioProcessorEditor (ConvolutionReverbAudioProcessor& p)
    : AudioProcessorEditor (&p), processor (p)
{
    //[Constructor_pre] You can add your own custom stuff here..
    //[/Constructor_pre]
    comboBox = std::unique_ptr<ComboBox>(new ComboBox ("new combo box"));
    addAndMakeVisible (*comboBox);
    comboBox->setEditableText (false);
    comboBox->setJustificationType (Justification::centredLeft);
    comboBox->setTextWhenNothingSelected (String());
    comboBox->setTextWhenNoChoicesAvailable (TRANS("FIR"));
    comboBox->addItem (TRANS("FIR"), 1);
    comboBox->addItem (TRANS("FFT"), 2);
    comboBox->addSeparator();
    comboBox->addListener (this);
    label2 = std::unique_ptr<Label>(new Label ("new label", TRANS("impulse response")));
    addAndMakeVisible (*label2);
    label2->setFont (Font (15.00f, Font::plain).withTypefaceStyle ("Regular"));
    label2->setJustificationType (Justification::centredLeft);
    label2->setEditable (false, false, false);
    label2->setColour (TextEditor::textColourId, Colours::black);
    label2->setColour (TextEditor::backgroundColourId, Colour (0x00000000));
    impulse_response = std::unique_ptr<ImpulseVisualizer>(new ImpulseVisualizer (320, 160));
    addAndMakeVisible (*impulse_response);
    impulse_response->setName ("impulse response");
    knoblabel = std::unique_ptr<Label>(new Label ("new label",
                           TRANS("wet/dry\n"
                                 "balance")));
    addAndMakeVisible (*knoblabel);
    knoblabel->setFont (Font (15.60f, Font::plain).withTypefaceStyle ("Regular"));
    knoblabel->setJustificationType (Justification::centredLeft);
    knoblabel->setEditable (false, false, false);
    knoblabel->setColour (TextEditor::textColourId, Colours::black);
    knoblabel->setColour (TextEditor::backgroundColourId, Colour (0x00000000));
    balance_knob = std::unique_ptr<Slider>(new Slider ("new slider"));
    addAndMakeVisible (*balance_knob);
    balance_knob->setExplicitFocusOrder (1);
    balance_knob->setRange (0, 1, 0);
    balance_knob->setSliderStyle (Slider::RotaryHorizontalVerticalDrag);
    balance_knob->setTextBoxStyle (Slider::TextBoxBelow, false, 80, 20);
    balance_knob->setColour (Slider::thumbColourId, Colour (0xff8d00ad));
    balance_knob->addListener (this);
    srtverb = std::unique_ptr<Label>(new Label ("new label",
                                                TRANS("srtverb")));
    addAndMakeVisible (*srtverb);
    srtverb->setFont (Font (35.20f, Font::plain).withTypefaceStyle ("Regular").withExtraKerningFactor (0.500f));
    srtverb->setJustificationType (Justification::centred);
    srtverb->setEditable (false, false, false);
    srtverb->setColour (TextEditor::textColourId, Colours::black);
    srtverb->setColour (TextEditor::backgroundColourId, Colour (0x00000000));
    
    
    //[UserPreSize]
    //[/UserPreSize]
    
    setSize (800, 600);
    
    
    //[Constructor] You can add your own custom stuff here..
    //[/Constructor]
}

ConvolutionReverbAudioProcessorEditor::~ConvolutionReverbAudioProcessorEditor()
{
    comboBox.release();
    label2.release();
    impulse_response.release();
    knoblabel.release();
    balance_knob.release();
    srtverb.release();
}

//==============================================================================
void ConvolutionReverbAudioProcessorEditor::paint (Graphics& g)
{
    g.fillAll (Colour (0xff7000e7));
}

void ConvolutionReverbAudioProcessorEditor::resized()
{
    //[UserPreResize] Add your own custom resize code here..
    //[/UserPreResize]
    
    comboBox->setBounds (proportionOfWidth (0.0000f), proportionOfHeight (0.0000f), proportionOfWidth (0.2103f), proportionOfHeight (0.0417f));
    label2->setBounds (proportionOfWidth (0.4016f), proportionOfHeight (0.2759f), proportionOfWidth (0.1574f), proportionOfHeight (0.0417f));
    impulse_response->setBounds (proportionOfWidth (0.0000f), proportionOfHeight (0.3194f), proportionOfWidth (0.9986f), proportionOfHeight (0.2741f));
    knoblabel->setBounds (proportionOfWidth (0.4451f), proportionOfHeight (0.7405f), proportionOfWidth (0.1086f), proportionOfHeight (0.0563f));
    balance_knob->setBounds (proportionOfWidth (0.4016f), proportionOfHeight (0.7986f), proportionOfWidth (0.1682f), proportionOfHeight (0.1506f));
    srtverb->setBounds (proportionOfWidth (0.3365f), proportionOfHeight (0.0000f), proportionOfWidth (0.3256f), proportionOfHeight (0.1597f));
    //[UserResized] Add your own custom resize handling here..
    balance_knob->setValue(0.5);
    //[/UserResized]
}

void ConvolutionReverbAudioProcessorEditor::changeListenerCallback (ChangeBroadcaster* source)
{
    impulse_response->change(source);
}

bool ConvolutionReverbAudioProcessorEditor::isInterestedInFileDrag (const StringArray &files)
{
    printf("interested in file drag\n");
    return true;
}

void ConvolutionReverbAudioProcessorEditor::filesDropped (const StringArray &files, int, int)
{
    printf("file name: %s\n", files[0].toRawUTF8());
    File file(files[0]);
    
    // set processor impulse
    this->processor.setImpulseResponse(file);
    
    // set thumbnail
    this->impulse_response->setThumbnail(new FileInputSource (file));
    
}

void ConvolutionReverbAudioProcessorEditor::comboBoxChanged (ComboBox* comboBoxThatHasChanged)
{
    //[UsercomboBoxChanged_Pre]
    //[/UsercomboBoxChanged_Pre]
    
    if (comboBoxThatHasChanged == comboBox.get())
    {
        //[UserComboBoxCode_comboBox] -- add your combo box handling code here..
        //[/UserComboBoxCode_comboBox]
    }
    
    //[UsercomboBoxChanged_Post]
    //[/UsercomboBoxChanged_Post]
}

void ConvolutionReverbAudioProcessorEditor::sliderValueChanged (Slider* sliderThatWasMoved)
{
    //[UsersliderValueChanged_Pre]
    //[/UsersliderValueChanged_Pre]
    
    if (sliderThatWasMoved == balance_knob.get())
    {
        //[UserSliderCode_balance_knob] -- add your slider handling code here..
        //AudioPlayer::setBalance(float(balance_knob->getValue()));
        this->processor.setBalance(float(balance_knob->getValue()));
        //[/UserSliderCode_balance_knob]
    }
    
    //[UsersliderValueChanged_Post]
    //[/UsersliderValueChanged_Post]
}
