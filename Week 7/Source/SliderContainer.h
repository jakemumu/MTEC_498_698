/*
  ==============================================================================

    SliderContainer.h
    Created: 6 Mar 2023 4:28:23pm
    Author:  Jacob Penn

  ==============================================================================
*/

#pragma once

#include "JuceHeader.h"

class SliderContainer : public juce::Component {
public:
    
    /* */
    SliderContainer();
    
    /* */
    void setParameterToControl(juce::AudioProcessorValueTreeState& inVTS, const juce::String& inParamID);
    
    /* */
    void resized() override;
    
private:
    
    juce::Slider mSlider;
    juce::Label mLabel;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> mAttachment;
};
