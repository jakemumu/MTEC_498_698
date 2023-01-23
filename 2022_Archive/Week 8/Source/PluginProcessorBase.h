/*
  ==============================================================================

    PluginProcessorBase.h
    Created: 15 Mar 2022 11:34:26am
    Author:  Jacob Penn

  ==============================================================================
*/

#pragma once

#include "JuceHeader.h"

class PluginProcessorBase : public juce::AudioProcessor
{
public:
    
    /* */
    PluginProcessorBase();
    
    /* */
    virtual ~PluginProcessorBase();
    
    bool hasEditor() const override;
    //==============================================================================
    /* general functions which tell the DAW information about your plugin -- you made need sometimes */
    const juce::String getName() const override;
    bool acceptsMidi() const override;
    bool producesMidi() const override;
    bool isMidiEffect() const override;
    double getTailLengthSeconds() const override;
    int getNumPrograms() override;
    int getCurrentProgram() override;
    void setCurrentProgram (int index) override;
    const juce::String getProgramName (int index) override;
    void changeProgramName (int index, const juce::String& newName) override;
    void releaseResources() override;
   #ifndef JucePlugin_PreferredChannelConfigurations
    bool isBusesLayoutSupported (const BusesLayout& layouts) const override;
   #endif
    
private:
    
};
