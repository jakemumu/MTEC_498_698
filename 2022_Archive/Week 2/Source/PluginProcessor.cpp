/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
Week2PluginAudioProcessor::Week2PluginAudioProcessor()
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

Week2PluginAudioProcessor::~Week2PluginAudioProcessor()
{
}

//==============================================================================
const juce::String Week2PluginAudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool Week2PluginAudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool Week2PluginAudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

bool Week2PluginAudioProcessor::isMidiEffect() const
{
   #if JucePlugin_IsMidiEffect
    return true;
   #else
    return false;
   #endif
}

double Week2PluginAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int Week2PluginAudioProcessor::getNumPrograms()
{
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
                // so this should be at least 1, even if you're not really implementing programs.
}

int Week2PluginAudioProcessor::getCurrentProgram()
{
    return 0;
}

void Week2PluginAudioProcessor::setCurrentProgram (int index)
{
}

const juce::String Week2PluginAudioProcessor::getProgramName (int index)
{
    return {};
}

void Week2PluginAudioProcessor::changeProgramName (int index, const juce::String& newName)
{
}

//==============================================================================
void Week2PluginAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    // Initialize our sine wave
    mSineWave.initialize(442, sampleRate);
}

void Week2PluginAudioProcessor::releaseResources()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool Week2PluginAudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
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

void Week2PluginAudioProcessor::processBlock (juce::AudioBuffer<float>& buffer, juce::MidiBuffer& midiMessages)
{
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
    
    // Left channel = 0 in the audio buffer
    int left = 0;
    
    // Right channel = 1 in the audio buffer
    int right = 1;
    
    // FOR EACH SAMPLE IN THE INCOMING AUDIO BUFFER
    for (int sample_index = 0; sample_index < buffer.getNumSamples(); sample_index++) {
        
        // GET THE NEXT SAMPLE FROM OUR SINE GENERATOR
        float output = mSineWave.getNextSample();
                
        // STORE THE OUTPUT TO THE LEFT AND RIGHT CHANNELS OF THE AUDIO BUFFER
        
        // FROM JUCE:
        // void setSample (int destChannel, int destSample, Type newValue)
        
        buffer.setSample(left, sample_index, output);
        
        buffer.setSample(right, sample_index, output);
        
    }
}

//==============================================================================
bool Week2PluginAudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

juce::AudioProcessorEditor* Week2PluginAudioProcessor::createEditor()
{
    return new Week2PluginAudioProcessorEditor (*this);
}

//==============================================================================
void Week2PluginAudioProcessor::getStateInformation (juce::MemoryBlock& destData)
{
    // You should use this method to store your parameters in the memory block.
    // You could do that either as raw data, or use the XML or ValueTree classes
    // as intermediaries to make it easy to save and load complex data.
}

void Week2PluginAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    // You should use this method to restore your parameters from this memory block,
    // whose contents will have been created by the getStateInformation() call.
}

//==============================================================================
// This creates new instances of the plugin..
juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new Week2PluginAudioProcessor();
}
