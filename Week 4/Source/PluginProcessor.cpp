/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
CoursePluginAudioProcessor::CoursePluginAudioProcessor()
     : AudioProcessor (BusesProperties()
                       .withInput  ("Input",  juce::AudioChannelSet::stereo(), true)
                       .withOutput ("Output", juce::AudioChannelSet::stereo(), true))
{
    /*
     
       NOTE:
     
       I know this code looks pretty intimidating and crumby -- sometimes we need to get into the trenches a bit when getting things
       setup in C++ -- however we only need to this one time for the application. Once we set this up we'll never touch this code
       again, and well use simpler looking code like in our sinewave class.
     
     */
    
    
    /* declare a vector of parameters */
    std::vector<std::unique_ptr<juce::RangedAudioParameter>> parameters;
    
    /* loop through our parameter defines and add the parameters to the vector */
    for (int i = 0; i < TotalNumberParameters; i++) {
        parameters.push_back(std::make_unique<juce::AudioParameterFloat>(PARAMETER_NAMES[i], PARAMETER_NAMES[i], PARAMETER_RANGES[i], 1.f));
    }
    
    /* construct the parameter tree object -- this will actually add all the parameters to our plugin */
    mParameterState.reset(new juce::AudioProcessorValueTreeState(*this, nullptr, "PARAMETER_STATE", { parameters.begin(), parameters.end() }));
    
    /* now lets get pointers which point to the current values of the parameters, we can use these in our processing loops */
    for (int i = 0; i < TotalNumberParameters; i++) {
        mParameterValues[i] = mParameterState->getRawParameterValue(PARAMETER_NAMES[i]);
    }
}

CoursePluginAudioProcessor::~CoursePluginAudioProcessor()
{
}

//==============================================================================
const juce::String CoursePluginAudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool CoursePluginAudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool CoursePluginAudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

bool CoursePluginAudioProcessor::isMidiEffect() const
{
   #if JucePlugin_IsMidiEffect
    return true;
   #else
    return false;
   #endif
}

double CoursePluginAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int CoursePluginAudioProcessor::getNumPrograms()
{
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
                // so this should be at least 1, even if you're not really implementing programs.
}

int CoursePluginAudioProcessor::getCurrentProgram()
{
    return 0;
}

void CoursePluginAudioProcessor::setCurrentProgram (int index)
{
}

const juce::String CoursePluginAudioProcessor::getProgramName (int index)
{
    return {};
}

void CoursePluginAudioProcessor::changeProgramName (int index, const juce::String& newName)
{
}

//==============================================================================
void CoursePluginAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    // Initialize our sine wave
    mSineWave1.initialize(442, sampleRate);
}

void CoursePluginAudioProcessor::releaseResources()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool CoursePluginAudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
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

void CoursePluginAudioProcessor::processBlock (juce::AudioBuffer<float>& buffer, juce::MidiBuffer& midiMessages)
{
    juce::ScopedNoDenormals noDenormals;
    auto totalNumInputChannels  = getTotalNumInputChannels();
    auto totalNumOutputChannels = getTotalNumOutputChannels();

    for (auto i = totalNumInputChannels; i < totalNumOutputChannels; ++i)
        buffer.clear (i, 0, buffer.getNumSamples());
    
    mSineWave1.setGain(mParameterValues[SineOscillator1Gain]->load());
    
    for (int sample_index = 0; sample_index < buffer.getNumSamples(); sample_index++) {
        
        float output = mSineWave1.getNextSample();
            
        buffer.setSample(0, sample_index, output);
        buffer.setSample(1, sample_index, output);
        
    }
}

juce::AudioProcessorValueTreeState& CoursePluginAudioProcessor::getValueTreeState()
{
    return *mParameterState.get();
}

//==============================================================================
bool CoursePluginAudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

juce::AudioProcessorEditor* CoursePluginAudioProcessor::createEditor()
{
    return new CoursePluginAudioProcessorEditor (*this);
}

//==============================================================================
void CoursePluginAudioProcessor::getStateInformation(juce::MemoryBlock& destData)
{
    // Get the underlying ValueTree from out "Parameter Value Tree"
    auto tree_state = mParameterState->copyState();
    
    // Convert the value tree into an XML object which can be saved on disk to as binary
    std::unique_ptr<juce::XmlElement> xml(tree_state.createXml());
    
    /* */
    DBG(xml->toString());

    /* store as binary */
    copyXmlToBinary(*xml, destData);
    
}

void CoursePluginAudioProcessor::setStateInformation(const void* data, int sizeInBytes)
{
    std::unique_ptr<juce::XmlElement> xmlState(getXmlFromBinary(data, sizeInBytes));

    if (xmlState.get()) {
        
        DBG(xmlState->toString());
        
        juce::ValueTree parameter_tree = juce::ValueTree::fromXml(*xmlState);
        mParameterState->replaceState(parameter_tree);
        
    }
}

//==============================================================================
// This creates new instances of the plugin..
juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new CoursePluginAudioProcessor();
}
