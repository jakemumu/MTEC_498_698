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
  mParameterManager(this)
{
    
}

Week6DelayAudioProcessor::~Week6DelayAudioProcessor()
{
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

    for (auto i = totalNumInputChannels; i < totalNumOutputChannels; ++i)
        buffer.clear (i, 0, buffer.getNumSamples());
    
    mDelayL.setParameters(mParameterManager.getCurrentParameterValue(Time),
                          mParameterManager.getCurrentParameterValue(Feedback),
                          mParameterManager.getCurrentParameterValue(Mix),
                          mParameterManager.getCurrentParameterValue(Lowpass),
                          mParameterManager.getCurrentParameterValue(Highpass));
    
    mDelayR.setParameters(mParameterManager.getCurrentParameterValue(Time),
                          mParameterManager.getCurrentParameterValue(Feedback),
                          mParameterManager.getCurrentParameterValue(Mix),
                          mParameterManager.getCurrentParameterValue(Lowpass),
                          mParameterManager.getCurrentParameterValue(Highpass));
    
    mDelayL.processBlock(buffer.getWritePointer(0), buffer.getNumSamples());
    mDelayR.processBlock(buffer.getWritePointer(1), buffer.getNumSamples());
}

// STATE
//==============================================================================
void Week6DelayAudioProcessor::getStateInformation(juce::MemoryBlock& destData)
{
    auto state = mParameterManager.getTreeState().copyState();
    std::unique_ptr<juce::XmlElement> xml(state.createXml());
    copyXmlToBinary(*xml, destData);
}

void Week6DelayAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    std::unique_ptr<juce::XmlElement> xmlState(getXmlFromBinary (data, sizeInBytes));
    mParameterManager.getTreeState().replaceState(juce::ValueTree::fromXml(*xmlState));
}

ParameterManager* Week6DelayAudioProcessor::getParameterManager()
{
    return &mParameterManager;
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
