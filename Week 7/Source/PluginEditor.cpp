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
    
    setLookAndFeel(&mLookAndFeel);
    
    typedef juce::AudioProcessorValueTreeState::SliderAttachment SliderAttachment;
    auto value_tree = audioProcessor.getParameterManager()->getValueTree();
    
    for (int i = 0; i < TotalNumberParameters; i++) {
        // Create the slider
        Slider* slider = new Slider();
        slider->setSliderStyle(juce::Slider::SliderStyle::RotaryVerticalDrag);
        slider->setTextBoxStyle(juce::Slider::TextBoxBelow, false, 150, 20);
        addAndMakeVisible(slider);
        
        mSliders.add(slider);
        
        // Create the attachment
        SliderAttachment* attachment = new SliderAttachment(*value_tree, PARAMETER_NAMES[i], *slider);
        mSliderAttachments.add(attachment);
    }
    
    setSize(TotalNumberParameters * 100, 120);
}

CoursePluginAudioProcessorEditor::~CoursePluginAudioProcessorEditor()
{
    setLookAndFeel(nullptr);
}

//==============================================================================
void CoursePluginAudioProcessorEditor::paint(juce::Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    
    g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));
    
    g.setColour(juce::Colours::white);
    g.setFont(juce::Font(12));
    
    for (int i = 0; i < TotalNumberParameters; i++) {
        g.drawText(PARAMETER_NAMES[i], mSliders[i]->getX(), mSliders[i]->getBottom(), 100, 20, Justification::centred);
    }
}

void CoursePluginAudioProcessorEditor::resized()
{
    for (int i = 0; i < TotalNumberParameters; i++) {
        mSliders[i]->setBounds(100 * i, 0, 100, 100);
    }
}
