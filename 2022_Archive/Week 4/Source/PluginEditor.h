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
class CoursePluginAudioProcessorEditor  : public juce::AudioProcessorEditor
{
public:
    
    // We see our processor comes into this editor class throug it's constructor
    CoursePluginAudioProcessorEditor (CoursePluginAudioProcessor&);
    
    ~CoursePluginAudioProcessorEditor() override;

    
    /*
        The paint function is where we put our graphical code.
        
        It will be drawn when significant changes happen to the system,
     
        or manually when we call repaint() on this class.
     */
    void paint (juce::Graphics&) override;
    
    /*
        The resized function is for performing layout
        
        It will be called when the size of our component changes.
     */
    void resized() override;

private:
    
    /*======= SLIDER 1 ======= */
    
    /* The Slider Member For Our UI */
    juce::Slider mGainAmountSlider;
    /* This is a helpful juce class to attach our slider to our value tree */
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> mGainAmountSliderAttachment;
    
    /* The Slider Member For Our UI */
    juce::Slider mFMAmountSlider;
    /* This is a helpful juce class to attach our slider to our value tree */
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> mFMAmountSliderAttachment;
    
    
    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    CoursePluginAudioProcessor& audioProcessor;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (CoursePluginAudioProcessorEditor)
};
