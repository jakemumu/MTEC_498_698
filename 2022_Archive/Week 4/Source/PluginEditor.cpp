/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"
#include "ParameterDefines.h"

//==============================================================================
CoursePluginAudioProcessorEditor::CoursePluginAudioProcessorEditor (CoursePluginAudioProcessor& p)
    : AudioProcessorEditor (&p), audioProcessor (p)
{
    // Lets set the properties we want to initialize on the slider.
    // Dont forget you can right click the name of classes, and select jump to
    // definition in order to see their available functions you can call.
    
    mGainAmountSlider.setSliderStyle(juce::Slider::SliderStyle::RotaryVerticalDrag);
    mGainAmountSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 150, 20);
    addAndMakeVisible(mGainAmountSlider);
    
    mFMAmountSlider.setSliderStyle(juce::Slider::SliderStyle::RotaryVerticalDrag);
    mFMAmountSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 150, 20);
    addAndMakeVisible(mFMAmountSlider);
    
    // Instead of using the lambda we used before -- we'll use this JUCE helper class which
    // connects our slider directly to our parameter tree -- previously we were treating gain as a
    // "property" -- the lambda is how to connect to those, now we're using parameters -- we can use
    // the slider attachments for those.
    
    mGainAmountSliderAttachment.reset(new juce::AudioProcessorValueTreeState::SliderAttachment(audioProcessor.getValueTreeState(),
                                                                                               PARAMETER_NAMES[GAIN_AMOUNT],
                                                                                               mGainAmountSlider));
    
    mFMAmountSliderAttachment.reset(new juce::AudioProcessorValueTreeState::SliderAttachment(audioProcessor.getValueTreeState(),
                                                                                             PARAMETER_NAMES[FM_AMOUNT],
                                                                                             mFMAmountSlider));
    
    setSize(400, 300);
}

CoursePluginAudioProcessorEditor::~CoursePluginAudioProcessorEditor()
{
}

//==============================================================================
void CoursePluginAudioProcessorEditor::paint(juce::Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    
    g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));

}

void CoursePluginAudioProcessorEditor::resized()
{
    mGainAmountSlider.setBounds(0, 0, 150, 150);
    mFMAmountSlider.setBounds(150, 0, 150, 150);
}
