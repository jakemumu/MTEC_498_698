/*
  ==============================================================================

    ParameterManager.h
    Created: 6 Mar 2023 5:07:12pm
    Author:  Jacob Penn

  ==============================================================================
*/

#pragma once

#include "JuceHeader.h"
#include "ParameterDefines.h"

class ParameterManager {
public:
    
    /* */
    ParameterManager(juce::AudioProcessor* inOwnerProcessor);
    
    /* */
    juce::AudioProcessorValueTreeState::ParameterLayout getParameterLayout();
    
    /* */
    juce::AudioProcessorValueTreeState& getTreeState();
    
    /* */
    float getCurrentParameterValue(AppParameterID inParameterID);
    
private:
    
    juce::Array<std::atomic<float>*> mParameterValues;
    juce::AudioProcessorValueTreeState mParameterState;
};
