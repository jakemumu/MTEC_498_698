/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
void Week3SineGeneratorAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    // [Gain Smoothing] Step 2: Initialize the smoothed value and set it's speed
    mSmoothedGain.reset(sampleRate, 0.01);
    
    // [Gain Smoothing] Step 3: Initialize the current value of the gain
    mSmoothedGain.setCurrentAndTargetValue(0.5f);
    
    mDelay.setSampleRate(sampleRate);
}


void Week3SineGeneratorAudioProcessor::processBlock(juce::AudioBuffer<float>& buffer, juce::MidiBuffer& midiMessages)
{
    /* boiler plate stuff to not touch */
    
    juce::ScopedNoDenormals noDenormals;
    auto totalNumInputChannels  = getTotalNumInputChannels();
    auto totalNumOutputChannels = getTotalNumOutputChannels();

    // In case we have more outputs than inputs, this code clears any output
    // channels that didn't contain input data, (because these aren't
    // guaranteed to be empty - they may contain garbage).
    // This is here to avoid people getting screaming feedback
    // when they first compile a plugin, but obviously you don't need to keep
    // this code if your algorithm always overwrites all the output channels.
    for (auto i = totalNumInputChannels; i < totalNumOutputChannels; ++i)
        buffer.clear (i, 0, buffer.getNumSamples());

    // sine w/ delay
    for (int sample = 0; sample < buffer.getNumSamples(); sample++) {

        phase += (440.f / getSampleRate());

        // [Gain Smoothing] Step 4: Get the next smooth gain value and apply it to the sine.
        float gain = mSmoothedGain.getNextValue();
        
        float out_left = sin(juce::MathConstants<float>::twoPi * phase) * gain;
        float out_right = out_left;
        
        mDelay.processSample(out_left, out_right);
        
        buffer.setSample(0, sample, out_left);
        buffer.setSample(1, sample, out_right);
    }
}

/* */
void Week3SineGeneratorAudioProcessor::setGain(float inGain)
{
    // do something when the gain changes
    mSmoothedGain.setTargetValue(inGain);
}

/* */
float Week3SineGeneratorAudioProcessor::getGain()
{
    return mSmoothedGain.getCurrentValue();
}





























//==============================================================================
Week3SineGeneratorAudioProcessor::Week3SineGeneratorAudioProcessor()
#ifndef JucePlugin_PreferredChannelConfigurations
     : AudioProcessor (BusesProperties()
                     #if ! JucePlugin_IsMidiEffect
                      #if ! JucePlugin_IsSynth
                       .withInput  ("Input",  juce::AudioChannelSet::stereo(), true)
                      #endif
                       .withOutput ("Output", juce::AudioChannelSet::stereo(), true)
                     #endif
                       )
#endif
{
}


Week3SineGeneratorAudioProcessor::~Week3SineGeneratorAudioProcessor()
{
}

//==============================================================================
const juce::String Week3SineGeneratorAudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool Week3SineGeneratorAudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool Week3SineGeneratorAudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

bool Week3SineGeneratorAudioProcessor::isMidiEffect() const
{
   #if JucePlugin_IsMidiEffect
    return true;
   #else
    return false;
   #endif
}

double Week3SineGeneratorAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int Week3SineGeneratorAudioProcessor::getNumPrograms()
{
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
                // so this should be at least 1, even if you're not really implementing programs.
}

int Week3SineGeneratorAudioProcessor::getCurrentProgram()
{
    return 0;
}

void Week3SineGeneratorAudioProcessor::setCurrentProgram (int index)
{
}

const juce::String Week3SineGeneratorAudioProcessor::getProgramName (int index)
{
    return {};
}

void Week3SineGeneratorAudioProcessor::changeProgramName (int index, const juce::String& newName)
{
}

void Week3SineGeneratorAudioProcessor::releaseResources()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool Week3SineGeneratorAudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
{
  #if JucePlugin_IsMidiEffect
    juce::ignoreUnused (layouts);
    return true;
  #else
    // This is the place where you check if the layout is supported.
    // In this template code we only support mono or stereo.
    // Some plugin hosts, such as certain GarageBand versions, will only
    // load plugins that support stereo bus layouts.
    if (layouts.getMainOutputChannelSet() != juce::AudioChannelSet::mono()
     && layouts.getMainOutputChannelSet() != juce::AudioChannelSet::stereo())
        return false;

    // This checks if the input layout matches the output layout
   #if ! JucePlugin_IsSynth
    if (layouts.getMainOutputChannelSet() != layouts.getMainInputChannelSet())
        return false;
   #endif

    return true;
  #endif
}
#endif

//==============================================================================
bool Week3SineGeneratorAudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

juce::AudioProcessorEditor* Week3SineGeneratorAudioProcessor::createEditor()
{
    return new Week3SineGeneratorAudioProcessorEditor (*this);
}

//==============================================================================
void Week3SineGeneratorAudioProcessor::getStateInformation (juce::MemoryBlock& destData)
{
    // You should use this method to store your parameters in the memory block.
    // You could do that either as raw data, or use the XML or ValueTree classes
    // as intermediaries to make it easy to save and load complex data.
}

void Week3SineGeneratorAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    // You should use this method to restore your parameters from this memory block,
    // whose contents will have been created by the getStateInformation() call.
}

//==============================================================================
// This creates new instances of the plugin..
juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new Week3SineGeneratorAudioProcessor();
}
