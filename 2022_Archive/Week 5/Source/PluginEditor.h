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
        
    juce::Slider mGainAmountSlider;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> mGainAmountSliderAttachment;
    
    juce::Slider mFMAmountSlider;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> mFMAmountSliderAttachment;
    
    juce::Slider mFMFreqSlider;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> mFMFreqSliderAttachment;
    
    juce::Slider mDelayTimeSecondsSlider;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> mDelayTimeSecondsSliderAttachment;
    
    juce::Slider mDelayFeedbackSlider;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> mDelayFeedbackSliderAttachment;
    
    juce::Slider mDelayMixSlider;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> mDelayMixSliderAttachment;
    
    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    CoursePluginAudioProcessor& audioProcessor;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (CoursePluginAudioProcessorEditor)
};
