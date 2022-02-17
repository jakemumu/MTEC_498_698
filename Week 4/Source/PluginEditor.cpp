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
    
    mSineWave1GainSlider.setSliderStyle(juce::Slider::SliderStyle::RotaryVerticalDrag);
    mSineWave1GainSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 150, 20);
    addAndMakeVisible(mSineWave1GainSlider);
    
    // Instead of using the lambda we used before -- we'll use this JUCE helper class which
    // connects our slider directly to our parameter tree -- previously we were treating gain as a
    // "property" -- the lambda is how to connect to those, now we're using parameters -- we can use
    // the slider attachments for those.
    
    mSineWave1GainSliderAttachment.reset(new juce::AudioProcessorValueTreeState::SliderAttachment(audioProcessor.getValueTreeState(),
                                                                                                  PARAMETER_NAMES[SineOscillator1Gain],
                                                                                                  mSineWave1GainSlider));
    
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
    // Here we setup where the sine wave is on screen.
    
    mSineWave1GainSlider.setBounds(0, 0, 150, 150);
}
