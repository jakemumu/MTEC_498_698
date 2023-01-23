/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
CoursePluginAudioProcessor::CoursePluginAudioProcessor()
{
    mParameterManager.reset(new ParameterManager(this));
    mPresetManager.reset(new PresetManager(this));
    mPropertyManager.reset(new PropertyManager(this));
}

CoursePluginAudioProcessor::~CoursePluginAudioProcessor()
{
}

//==============================================================================
void CoursePluginAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    mDelayLeft.initialize(sampleRate, samplesPerBlock);
    mDelayRight.initialize(sampleRate, samplesPerBlock);
}

void CoursePluginAudioProcessor::processBlock (juce::AudioBuffer<float>& buffer, juce::MidiBuffer& midiMessages)
{
    juce::ScopedNoDenormals noDenormals;
    auto totalNumInputChannels  = getTotalNumInputChannels();
    auto totalNumOutputChannels = getTotalNumOutputChannels();

    for (auto i = totalNumInputChannels; i < totalNumOutputChannels; ++i)
        buffer.clear (i, 0, buffer.getNumSamples());
    
    if (wrapperType == AudioProcessor::wrapperType_Standalone && SIMPLE_SAMPLE_IN_STANDALONE) {
        _generateSimpleSample(buffer);
    }
    
    float input_gain = 0;
    input_gain += buffer.getRMSLevel(0, 0, buffer.getNumSamples());
    input_gain += buffer.getRMSLevel(1, 0, buffer.getNumSamples());
    input_gain /= 2;
    mInputGain = input_gain;
    
    mDelayLeft.setParameters(mParameterManager->getCurrentValue(DELAY_TIME_SECONDS),
                             mParameterManager->getCurrentValue(DELAY_FEEDBACK),
                             mParameterManager->getCurrentValue(DELAY_MIX),
                             mParameterManager->getCurrentValue(DELAY_FEEDBACK_LOWPASS),
                             mParameterManager->getCurrentValue(DELAY_FEEDBACK_HIGHPASS));
    
    mDelayRight.setParameters(mParameterManager->getCurrentValue(DELAY_TIME_SECONDS),
                              mParameterManager->getCurrentValue(DELAY_FEEDBACK),
                              mParameterManager->getCurrentValue(DELAY_MIX),
                              mParameterManager->getCurrentValue(DELAY_FEEDBACK_LOWPASS),
                              mParameterManager->getCurrentValue(DELAY_FEEDBACK_HIGHPASS));
    
    mDelayLeft.processBlock(buffer.getWritePointer(0), buffer.getNumSamples());
    mDelayRight.processBlock(buffer.getWritePointer(1), buffer.getNumSamples());
    
    float output_gain = 0;
    output_gain += buffer.getRMSLevel(0, 0, buffer.getNumSamples());
    output_gain += buffer.getRMSLevel(1, 0, buffer.getNumSamples());
    output_gain /= 2;
    mOutputGain = output_gain;
}

ParameterManager* CoursePluginAudioProcessor::getParameterManager()
{
    return mParameterManager.get();
}

PresetManager* CoursePluginAudioProcessor::getPresetManager()
{
    return mPresetManager.get();
}

AudioProcessor* CoursePluginAudioProcessor::getAudioProcessor()
{
    return this;
}

PropertyManager* CoursePluginAudioProcessor::getPropertyManager()
{
    return mPropertyManager.get();
}

juce::AudioProcessorEditor* CoursePluginAudioProcessor::createEditor()
{
    return new CoursePluginAudioProcessorEditor (*this);
}

//==============================================================================
void CoursePluginAudioProcessor::getStateInformation(juce::MemoryBlock& destData)
{
    // Get the underlying ValueTree from out "Parameter Value Tree"
    auto parameter_state = mParameterManager->getValueTree()->copyState();
    
    // Convert the value tree into an XML object which can be saved on disk to as binary
    std::unique_ptr<juce::XmlElement> xml(parameter_state.createXml());
    
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
        mParameterManager->getValueTree()->replaceState(parameter_tree);
        
    }
}

void CoursePluginAudioProcessor::_generateSimpleSample(AudioBuffer<float>& inBuffer)
{
#if SIMPLE_SAMPLE_IN_STANDALONE
    static int mPhase = 0;
    
    if (!mTestingSample.isFileLoaded()) {
        
        File dir = File::getSpecialLocation(File::SpecialLocationType::currentExecutableFile);
        
        String dir_name = dir.getFileName();
        
        while (dir_name.contains("Week") == false) {
            dir = dir.getParentDirectory();
            dir_name = dir.getFileName();
        }
        
        String file_name = "break.wav";
        
        File sample = dir
        .getChildFile("Test_Audio")
        .getChildFile(file_name);

        mTestingSample.loadFile(sample);
    }
    
    for (int i = 0; i < inBuffer.getNumSamples(); i++) {
        std::vector<float> samples(2);
        mTestingSample.getSample(mPhase, samples);
        inBuffer.setSample(0, i, samples[0]);
        inBuffer.setSample(1, i, samples[1]);
        mPhase += 1;
        if (mPhase >= mTestingSample.getLengthInSamples()) {
            mPhase = 0;
        }
    }
#endif
}

float CoursePluginAudioProcessor::getGain(bool returnOutput)
{
    if (returnOutput) {
        return mOutputGain;
    } else {
        return mInputGain;
    }
}

//==============================================================================
// This creates new instances of the plugin..
juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new CoursePluginAudioProcessor();
}
