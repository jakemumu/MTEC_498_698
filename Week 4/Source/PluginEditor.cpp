/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
CoursePluginAudioProcessorEditor::CoursePluginAudioProcessorEditor (CoursePluginAudioProcessor& p)
    : AudioProcessorEditor (&p), audioProcessor (p)
{
    // Lets set the properties we want to initialize on the slider.
    // Dont forget you can right click the name of classes, and select jump to
    // definition in order to see their available functions you can call.
    
    mSlider.setSliderStyle(juce::Slider::SliderStyle::RotaryVerticalDrag);
    mSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 150, 20);
    mSlider.setRange(0.f, 1.f);
    addAndMakeVisible(mSlider);
    
    
    // This is called a LAMBDA expression, it is used in various programming
    // languages but this is how we construct them in C++, it's one of the few
    // "advanced" language features well use in this course.
    
    // this is saying "when the slider values changes, please take our reference of our
    // audio engine / plugin, and set our sine volume, to the current value of our slider.
    
    // JUCE manages calling this function for you, when you move the slider on the screen.
    
    mSlider.onValueChange = [this]() {
        audioProcessor.getSineWave1()->setGain(mSlider.getValue());
    };
    
    
    // Here we simply update the value of our slider to the current value in the audio
    // engine. If we didn't do this, we'd see the slider at 0, even though the gain
    // of the sine in the audio engine was 1.f
    
    mSlider.setValue(audioProcessor.getSineWave1()->getGain());
    
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
    
    mSlider.setBounds(0, 0, 150, 150);
}
