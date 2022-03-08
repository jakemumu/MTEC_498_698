//
//  ParameterManager.cpp
//  Course Plugin - Shared Code
//
//  Created by Jacob Penn on 2/22/22.
//

#include "ParameterManager.h"
#include "ProcessorInterface.h"

/* */
ParameterManager::ParameterManager(ProcessorInterface* inInterface)
: mProcessorInterface(inInterface)
{
    /* declare a vector of parameters */
    std::vector<std::unique_ptr<juce::RangedAudioParameter>> parameters;
    
    /* loop through our parameter defines and add the parameters to the vector */
    for (int i = 0; i < TotalNumberParameters; i++) {
        parameters.push_back(std::make_unique<juce::AudioParameterFloat>(PARAMETER_NAMES[i],
                                                                         PARAMETER_NAMES[i],
                                                                         PARAMETER_RANGES[i],
                                                                         PARAMETER_DEFAULTS[i]));
    }
    
    /* construct the parameter tree object -- this will actually add all the parameters to our plugin */
    mParameterState.reset(new juce::AudioProcessorValueTreeState(*mProcessorInterface->getAudioProcessor(),
                                                                 nullptr,
                                                                 "PARAMETER_STATE",
                                                                 { parameters.begin(), parameters.end() }));
}

/* */
ParameterManager::~ParameterManager()
{
    
}

/* */
float ParameterManager::getCurrentValue(int inParameterID)
{
    return mParameterState->getRawParameterValue(PARAMETER_NAMES[inParameterID])->load();
}

juce::AudioProcessorValueTreeState* ParameterManager::getValueTree()
{
    return mParameterState.get();
}
