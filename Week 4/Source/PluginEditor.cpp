/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
Week3SineGeneratorAudioProcessorEditor::Week3SineGeneratorAudioProcessorEditor (Week3SineGeneratorAudioProcessor& p)
    : AudioProcessorEditor (&p), audioProcessor (p)
{
    // [Slider] - Step 2: Setup the graphical style of the slider

    // add slider as child (so it shows up on screen)
    mSlider.setSliderStyle(juce::Slider::SliderStyle::RotaryVerticalDrag);
    mSlider.setRange(0.f, 1.f);
    
    // [Slider] - Step 3: Set the sliders value to the correct default, or start

    mSlider.setValue(audioProcessor.getGain());
    
    
    // [Slider] - Step 4: Setup what should happen when the slider changes
    
    // this is called a lambda expression. A lamda expression is a function which you
    // may define while an application is running.

    // [this] is a capture clause, it provide the "context" for the functions internal
    // data. Saying "this" is available, is saying all members of "this" can be used
    // in this lamda.
    mSlider.onValueChange = [this] () {
        audioProcessor.setGain(mSlider.getValue());
    };
    
    
    // [Slider] - Step 5: Add the slider as a child and put it on the screen
    
    addAndMakeVisible(mSlider);
    
    
    // Make sure that before the constructor has finished, you've set the
    // editor's size to whatever you need it to be.
    setSize (400, 300);
}

Week3SineGeneratorAudioProcessorEditor::~Week3SineGeneratorAudioProcessorEditor()
{
}

//==============================================================================
void Week3SineGeneratorAudioProcessorEditor::paint (juce::Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));
}

void Week3SineGeneratorAudioProcessorEditor::resized()
{
    // [Slider] - Step 6: Setup where the slider will be shown on screen

    mSlider.setBounds(getLocalBounds());
    mSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, true, getWidth(), 20);
}

void Week3SineGeneratorAudioProcessorEditor::timerCallback()
{
    
}
