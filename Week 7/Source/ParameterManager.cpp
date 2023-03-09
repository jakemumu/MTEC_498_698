/*
  ==============================================================================

    ParameterManager.cpp
    Created: 6 Mar 2023 5:07:12pm
    Author:  Jacob Penn

  ==============================================================================
*/

#include "ParameterManager.h"

ParameterManager::ParameterManager(juce::AudioProcessor* inOwnerProcessor)
: mParameterState (*inOwnerProcessor, nullptr, juce::Identifier("ParamterState"), getParameterLayout())
{
    for (int i = 0; i < AppParameterID::TotalNumberParameters; i++) {
        mParameterValues.add(mParameterState.getRawParameterValue(ParameterIDStrings[i]));
    }
}

juce::AudioProcessorValueTreeState& ParameterManager::getTreeState()
{
    return mParameterState;
}

// here we actually define our params
juce::AudioProcessorValueTreeState::ParameterLayout ParameterManager::getParameterLayout()
{
    juce::AudioProcessorValueTreeState::ParameterLayout layout;
    
    for (int i = 0; i < AppParameterID::TotalNumberParameters; i++) {
        
        layout.add(std::make_unique<juce::AudioParameterFloat>(juce::ParameterID(ParameterIDStrings[i], 1),
                                                               ParameterIDStrings[i],
                                                               ParameterMinimum[i],
                                                               ParameterMaximum[i],
                                                               ParameterDefault[i]));
        
    }
    
    return layout;
}

float ParameterManager::getCurrentParameterValue(AppParameterID inParameterID)
{
    return mParameterValues[inParameterID]->load();
}
