/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"
#include "ParameterDefines.h"

//==============================================================================
Week6DelayAudioProcessorEditor::Week6DelayAudioProcessorEditor (Week6DelayAudioProcessor& p)
    : AudioProcessorEditor (&p), audioProcessor (p)
{
    auto& tree_state = audioProcessor.getParameterManager()->getTreeState();

    for (int i = 0; i < audioProcessor.getParameters().size(); i++) {
        mSliderContainers.add(new SliderContainer());
        mSliderContainers[i]->setParameterToControl(tree_state, ParameterIDStrings[i]);
        addAndMakeVisible(mSliderContainers[i]);
    }
    
    // Make sure that before the constructor has finished, you've set the
    // editor's size to whatever you need it to be.
    setSize (400, 300);
}

Week6DelayAudioProcessorEditor::~Week6DelayAudioProcessorEditor()
{
}

//==============================================================================
void Week6DelayAudioProcessorEditor::paint (juce::Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));
}

void Week6DelayAudioProcessorEditor::resized()
{
    auto bounds = getLocalBounds();
    int num_slider = mSliderContainers.size();
    for (int i = 0; i < mSliderContainers.size(); i++) {
        mSliderContainers[i]->setBounds(bounds.removeFromTop(getHeight()/num_slider));
    }
}
