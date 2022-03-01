/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

// INCLUDE OUR SINEWAVE
#include "SineWave.h"
#include "Delay.h"
#include "ParameterManager.h"

//==============================================================================
/**
*/
class CoursePluginAudioProcessor  : public juce::AudioProcessor
{
public:
    //==============================================================================
    CoursePluginAudioProcessor();
    ~CoursePluginAudioProcessor() override;

    //==============================================================================
    
    /*
     
     This function is called before audio playback in order to initialize objects which well use during
     audio processing.
       
     It will be called a single time, and then again if the user changes sample rates, block size, or
     does a bounce / export of the audio.
     
     */
    void prepareToPlay (double sampleRate, int samplesPerBlock) override;
    
    /*
     
     This function will be called continuously during playback, and is where we can modify
     or generate audio signals.
     
     */
    void processBlock (juce::AudioBuffer<float>&, juce::MidiBuffer&) override;
    
    /*
     The DAW calls this to get the current state of your plugin for saving data
     */
    void getStateInformation (juce::MemoryBlock& destData) override;

    /*
     The DAW calls this to set the current state of your plugin when sessions open
     */
    void setStateInformation (const void* data, int sizeInBytes) override;
    
    /* */
    ParameterManager* getParameterManager();
    
    /* called before destruction to free data (rarely used with modern cpp) */
    void releaseResources() override;

   #ifndef JucePlugin_PreferredChannelConfigurations
    bool isBusesLayoutSupported (const BusesLayout& layouts) const override;
   #endif

    //==============================================================================
    juce::AudioProcessorEditor* createEditor() override;
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

private:
    
    SineWave mSineWave1;
    SineWave mSineWave1FMOperator;
    
    Delay mDelayLeft;
    Delay mDelayRight;
    
    std::unique_ptr<ParameterManager> mParameterManager;
    
    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (CoursePluginAudioProcessor)
};
