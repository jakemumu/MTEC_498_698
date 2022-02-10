/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
Week2PluginAudioProcessorEditor::Week2PluginAudioProcessorEditor (Week2PluginAudioProcessor& p)
    : AudioProcessorEditor (&p), audioProcessor (p)
{
    setSize(400, 300);
}

Week2PluginAudioProcessorEditor::~Week2PluginAudioProcessorEditor()
{
}

//==============================================================================
void Week2PluginAudioProcessorEditor::paint(juce::Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));

}

void Week2PluginAudioProcessorEditor::resized()
{
    
}
