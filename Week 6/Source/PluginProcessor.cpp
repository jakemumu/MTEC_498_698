/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
Week6DelayAudioProcessor::Week6DelayAudioProcessor()
: AudioProcessor (BusesProperties()
                  .withInput  ("Input",  juce::AudioChannelSet::stereo(), true)
                  .withOutput ("Output", juce::AudioChannelSet::stereo(), true)),

  // construct our parameter state object
  mParameterState (*this, nullptr, juce::Identifier("ParamterState"), getParameterLayout())
{

}

Week6DelayAudioProcessor::~Week6DelayAudioProcessor()
{
}

// here we actually define our params
juce::AudioProcessorValueTreeState::ParameterLayout Week6DelayAudioProcessor::getParameterLayout()
{
    juce::AudioProcessorValueTreeState::ParameterLayout layout;
    
    // dry wet param
    layout.add(std::make_unique<juce::AudioParameterFloat>(juce::ParameterID("DryWet", 1),
                                                           "Dry / Wet",
                                                           0.0f,
                                                           1.0f,
                                                           0.5f));
    
    // time param
    layout.add(std::make_unique<juce::AudioParameterFloat>(juce::ParameterID("Time", 1),
                                                           "Time",
                                                           .1f,
                                                           1.0f,
                                                           0.5f));
    
    // feedback param
    layout.add(std::make_unique<juce::AudioParameterFloat>(juce::ParameterID("Feedback", 1),
                                                           "Feedback",
                                                           0.0f,
                                                           .9f,
                                                           0.5f));
    
    // lowpass param
    layout.add(std::make_unique<juce::AudioParameterFloat>(juce::ParameterID("Lowpass_Freq", 1),
                                                           "Lowpass",
                                                           20.f,
                                                           22000.f,
                                                           30.f));
    
    // highpass param
    layout.add(std::make_unique<juce::AudioParameterFloat>(juce::ParameterID("Highpass_Freq", 1),
                                                           "Highpass",
                                                           20.f,
                                                           20000.f,
                                                           20000.f));
    
    return layout;
}

// Audio
//==============================================================================
void Week6DelayAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    mDelayL.initialize(sampleRate, samplesPerBlock);
    mDelayR.initialize(sampleRate, samplesPerBlock);
}

void Week6DelayAudioProcessor::processBlock (juce::AudioBuffer<float>& buffer, juce::MidiBuffer& midiMessages)
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
    
    mDelayL.processBlock(buffer.getWritePointer(0), buffer.getNumSamples());
    mDelayR.processBlock(buffer.getWritePointer(1), buffer.getNumSamples());
}

// STATE
//==============================================================================
void Week6DelayAudioProcessor::getStateInformation(juce::MemoryBlock& destData)
{
    auto state = mParameterState.copyState();
    std::unique_ptr<juce::XmlElement> xml(state.createXml());
    copyXmlToBinary(*xml, destData);
}

void Week6DelayAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    std::unique_ptr<juce::XmlElement> xmlState(getXmlFromBinary (data, sizeInBytes));
    mParameterState.replaceState(juce::ValueTree::fromXml(*xmlState));
}























//==============================================================================
const juce::String Week6DelayAudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool Week6DelayAudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool Week6DelayAudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

bool Week6DelayAudioProcessor::isMidiEffect() const
{
   #if JucePlugin_IsMidiEffect
    return true;
   #else
    return false;
   #endif
}

double Week6DelayAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int Week6DelayAudioProcessor::getNumPrograms()
{
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
                // so this should be at least 1, even if you're not really implementing programs.
}

int Week6DelayAudioProcessor::getCurrentProgram()
{
    return 0;
}

void Week6DelayAudioProcessor::setCurrentProgram (int index)
{
}

const juce::String Week6DelayAudioProcessor::getProgramName (int index)
{
    return {};
}

void Week6DelayAudioProcessor::changeProgramName (int index, const juce::String& newName)
{
}

void Week6DelayAudioProcessor::releaseResources()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool Week6DelayAudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
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
bool Week6DelayAudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

juce::AudioProcessorEditor* Week6DelayAudioProcessor::createEditor()
{
    return new Week6DelayAudioProcessorEditor (*this);
}

//==============================================================================
// This creates new instances of the plugin..
juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new Week6DelayAudioProcessor();
}
