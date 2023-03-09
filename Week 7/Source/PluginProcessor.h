/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "Delay.h"
#include "ParameterManager.h"

//==============================================================================
/**
*/
class Week6DelayAudioProcessor  : public juce::AudioProcessor
                            #if JucePlugin_Enable_ARA
                             , public juce::AudioProcessorARAExtension
                            #endif
{
public:
    //==============================================================================
    Week6DelayAudioProcessor();
    ~Week6DelayAudioProcessor() override;

    
    
    //==============================================================================
    
    /* this gets called constantly & is where we do our audio processing */
    void processBlock (juce::AudioBuffer<float>&, juce::MidiBuffer&) override;
    
    /* this gets called when the sample rate changes or before process */
    void prepareToPlay (double sampleRate, int samplesPerBlock) override;
    
    
    //==============================================================================
    
    /* called right before the DAW saves a state / session */
    void getStateInformation (juce::MemoryBlock& destData) override;
    
    /* called when the user loads a session */
    void setStateInformation (const void* data, int sizeInBytes) override;


    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    void releaseResources() override;

   #ifndef JucePlugin_PreferredChannelConfigurations
    bool isBusesLayoutSupported (const BusesLayout& layouts) const override;
   #endif

    //==============================================================================
    juce::AudioProcessorEditor* createEditor() override;
    bool hasEditor() const override;

    //==============================================================================
    const juce::String getName() const override;

    bool acceptsMidi() const override;
    bool producesMidi() const override;
    bool isMidiEffect() const override;
    double getTailLengthSeconds() const override;

    //==============================================================================
    int getNumPrograms() override;
    int getCurrentProgram() override;
    void setCurrentProgram (int index) override;
    const juce::String getProgramName (int index) override;
    void changeProgramName (int index, const juce::String& newName) override;
    
    ParameterManager* getParameterManager();
    
private:

    ParameterManager mParameterManager;

    Delay mDelayL;
    Delay mDelayR;

    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (Week6DelayAudioProcessor)
};
