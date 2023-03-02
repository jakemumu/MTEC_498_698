/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
Week6DelayAudioProcessorEditor::Week6DelayAudioProcessorEditor (Week6DelayAudioProcessor& p)
    : AudioProcessorEditor (&p), audioProcessor (p)
{
    // lets make a slider for every parameter in our plugin
    
    // lets get our procesor tree
    auto& tree_state = audioProcessor.getTreeState();
        
    // now lets loop through our parameters
    for (int i = 0; i < audioProcessor.getParameters().size(); i++) {
        
        // lets cast our generic parameter to the float type (we know these are float type params because we created these)
        auto float_param = static_cast<juce::AudioParameterFloat*>(audioProcessor.getParameters()[i]);
        
        // lets make a slider
        auto slider = new juce::Slider();
        mSliders.add(slider);
        
        // create an attachment from JUCE
        auto attachment = new juce::AudioProcessorValueTreeState::SliderAttachment(tree_state, float_param->getParameterID(), *slider);
        
        // store the attachment -- we create it before we store it because it's a pointer and requires arguments into it's constructor.
        mAttachments.add(attachment);
        
        // make the slider visible
        addAndMakeVisible(slider);
        
        // make a label
        auto label = new juce::Label();

        mLabels.add(label);
        
        // set it's name
        label->setText(float_param->getName(10), juce::dontSendNotification);
        label->setJustificationType(juce::Justification::centred);
        
        // add it to array
        addAndMakeVisible(label);
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
    int num_slider = mSliders.size();
    
    for (int i = 0; i < mSliders.size(); i++) {
        mSliders[i]->setBounds(bounds.removeFromTop(getHeight()/num_slider));
        mLabels[i]->setBounds(mSliders[i]->getBounds().removeFromBottom(20));
    }
}
