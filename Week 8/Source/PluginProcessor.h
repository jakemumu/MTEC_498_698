/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

#include "InMemorySample.h"
#include "Delay.h"
#include "ParameterManager.h"
#include "PresetManager.h"
#include "PropertyManager.h"
#include "ProcessorInterface.h"
#include "PluginProcessorBase.h"
#include "Grain.h"

#define SIMPLE_SAMPLE_IN_STANDALONE 1

//==============================================================================
/**
*/
class CoursePluginAudioProcessor  : public PluginProcessorBase,
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
    PropertyManager* getPropertyManager() override;
    float getGain(bool returnOutput) override;

    //==============================================================================
    juce::AudioProcessorEditor* createEditor() override;
    
private:
    
    void _generateSimpleSample(AudioBuffer<float>& inBuffer);
    
    float mInputGain = 0;
    float mOutputGain = 0;
    
    Delay mDelayLeft;
    Delay mDelayRight;
    
    Grain mGrain;
    
#if SIMPLE_SAMPLE_IN_STANDALONE
    InMemorySample mTestingSample;
#endif
    
    std::unique_ptr<ParameterManager> mParameterManager;
    std::unique_ptr<PresetManager> mPresetManager;
    std::unique_ptr<PropertyManager> mPropertyManager;
    
    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (CoursePluginAudioProcessor)
};
