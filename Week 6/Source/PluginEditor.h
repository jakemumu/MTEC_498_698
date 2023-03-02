/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"

//==============================================================================
/**
*/
class Week6DelayAudioProcessorEditor  : public juce::AudioProcessorEditor
{
public:
    Week6DelayAudioProcessorEditor (Week6DelayAudioProcessor&);
    ~Week6DelayAudioProcessorEditor() override;

    //==============================================================================
    void paint (juce::Graphics&) override;
    void resized() override;

private:
        
    // the slider classes
    juce::OwnedArray<juce::Slider> mSliders;
    
    // labels for our sliders
    juce::OwnedArray<juce::Label> mLabels;
    
    // a slider attachment classes -- JUCE provides this as a way to easily connect
    // sliders to audio process value tree states, for a lot of applications, this will
    // be all you need to connect your UI & DSP together.
    juce::OwnedArray<juce::AudioProcessorValueTreeState::SliderAttachment> mAttachments;
    
    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    Week6DelayAudioProcessor& audioProcessor;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (Week6DelayAudioProcessorEditor)
};
