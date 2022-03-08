/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

// INCLUDE OUR SINEWAVE
#include "InMemorySample.h"
#include "Delay.h"
#include "ParameterManager.h"
#include "PresetManager.h"
#include "ProcessorInterface.h"

#define SIMPLE_SAMPLE_IN_STANDALONE 1

//==============================================================================
/**
*/
class CoursePluginAudioProcessor  : public juce::AudioProcessor,
                                    public ProcessorInterface
{
public:
    //==============================================================================
    CoursePluginAudioProcessor();
    ~CoursePluginAudioProcessor() override;

    //==============================================================================

    /* PRIMARY PROCESSOR RESPONSIBILITIES*/
    void prepareToPlay (double sampleRate, int samplesPerBlock) override;
    void processBlock (juce::AudioBuffer<float>&, juce::MidiBuffer&) override;
    void getStateInformation (juce::MemoryBlock& destData) override;
    void setStateInformation (const void* data, int sizeInBytes) override;
    
    /* PROCESSOR INTERACE OVERRIDES*/
    ParameterManager* getParameterManager() override;
    PresetManager* getPresetManager() override;
    AudioProcessor* getAudioProcessor() override;

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
    void releaseResources() override;
   #ifndef JucePlugin_PreferredChannelConfigurations
    bool isBusesLayoutSupported (const BusesLayout& layouts) const override;
   #endif

private:
    
    void _generateSimpleSample(AudioBuffer<float>& inBuffer);
    
    Delay mDelayLeft;
    Delay mDelayRight;
    
#if SIMPLE_SAMPLE_IN_STANDALONE
    InMemorySample mTestingSample;
#endif
    
    std::unique_ptr<ParameterManager> mParameterManager;
    std::unique_ptr<PresetManager> mPresetManager;
    
    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (CoursePluginAudioProcessor)
};
