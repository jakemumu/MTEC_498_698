/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

// INCLUDE OUR SINEWAVE
#include "SineWave.h"

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
     
     This is a function for the editor -- in order to update the value of the sinewave
    
     */
    void setSineVolume(float inInputVolumeAmp);
    
    /*
     
     This is a function for the editor -- in order to update the knob on screen to the current gain value
    
     */
    float getSineVolume();
    
    /* called before destruction to free data (rarely used with modern cpp) */
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

    //==============================================================================
    void getStateInformation (juce::MemoryBlock& destData) override;
    void setStateInformation (const void* data, int sizeInBytes) override;

private:
    
    SineWave mSineWave;
    float mSineGain = 1.f;
    
    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (CoursePluginAudioProcessor)
};
