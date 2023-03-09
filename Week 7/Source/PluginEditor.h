/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"
#include "SliderContainer.h"

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
    
    juce::OwnedArray<SliderContainer> mSliderContainers;
        
    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    Week6DelayAudioProcessor& audioProcessor;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (Week6DelayAudioProcessorEditor)
};
