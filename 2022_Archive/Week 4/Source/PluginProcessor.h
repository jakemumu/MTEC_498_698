/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

// INCLUDE OUR SINEWAVE
#include "SineWave.h"
#include "ParameterDefines.h"

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
    
    /*
     Returns the value tree state (our parameters) to the DAW
     */
    juce::AudioProcessorValueTreeState& getValueTreeState();
    
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
    
    /* this will be our "parameter tree" */
    std::unique_ptr<juce::AudioProcessorValueTreeState> mParameterState;
    
    /* this will hold the current value of the parameters */
    
    /* std::atomic is a C++ class which guarantees thread safe
       read and write access -- you don't need to worry about it
       to much for now -- you can just treat it like a regular float.
     */
    std::array<std::atomic<float>*, TotalNumberParameters> mParameterValues;
    
    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (CoursePluginAudioProcessor)
};
