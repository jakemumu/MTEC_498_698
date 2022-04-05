/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

//==============================================================================
/**
*/
class Synth_DemoAudioProcessor  : public juce::AudioProcessor
{
public:
    //==============================================================================
    Synth_DemoAudioProcessor();
    ~Synth_DemoAudioProcessor() override;

    //==============================================================================
    void prepareToPlay (double sampleRate, int samplesPerBlock) override;
    void releaseResources() override;

   #ifndef JucePlugin_PreferredChannelConfigurations
    bool isBusesLayoutSupported (const BusesLayout& layouts) const override;
   #endif

    void processBlock (juce::AudioBuffer<float>&, juce::MidiBuffer&) override;

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
    
    Synthesiser mSynthClass;
    
    struct SineWaveSound   : public SynthesiserSound
    {
        SineWaveSound() {}
     
        bool appliesToNote    (int) override        { return true; }
        bool appliesToChannel (int) override        { return true; }
    };
    
    class SineWaveVoice : public SynthesiserVoice
    {
    public:
        
        SineWaveVoice() {
            
        }
        
        ~SineWaveVoice() {
            
        }
        
        bool canPlaySound (SynthesiserSound* sound) override
        {
            return dynamic_cast<SineWaveSound*>(sound) != nullptr;
        }

        void startNote (int midiNoteNumber,
                        float velocity,
                        SynthesiserSound* sound,
                        int currentPitchWheelPosition) override
        {
            currentAngle = 0.0;
            level = velocity * 0.15;
            tailOff = 0.0;
     
            auto cyclesPerSecond = juce::MidiMessage::getMidiNoteInHertz(midiNoteNumber);
            auto cyclesPerSample = cyclesPerSecond / getSampleRate();
     
            angleDelta = cyclesPerSample * 2.0 * juce::MathConstants<double>::pi;
        }
        
        void stopNote (float velocity, bool allowTailOff) override
        {
            if (allowTailOff)
            {
                if (tailOff == 0.0)
                    tailOff = 1.0;
            }
            else
            {
                clearCurrentNote();
                angleDelta = 0.0;
            }
        }
        
        void pitchWheelMoved (int newPitchWheelValue) override
        {
            
        }

        void controllerMoved (int controllerNumber, int newControllerValue) override
        {
            
        }
        
        void renderNextBlock (AudioBuffer<float>& outputBuffer, int startSample, int numSamples) override
        {
            if (angleDelta != 0.0)
            {
                if (tailOff > 0.0) // [7]
                {
                    while (--numSamples >= 0)
                    {
                        auto currentSample = (float) (std::sin (currentAngle) * level * tailOff);
     
                        for (auto i = outputBuffer.getNumChannels(); --i >= 0;)
                            outputBuffer.addSample (i, startSample, currentSample);
     
                        currentAngle += angleDelta;
                        ++startSample;
     
                        tailOff *= 0.99; // [8]
     
                        if (tailOff <= 0.005)
                        {
                            clearCurrentNote(); // [9]
     
                            angleDelta = 0.0;
                            break;
                        }
                    }
                }
                else
                {
                    while (--numSamples >= 0) // [6]
                    {
                        auto currentSample = (float) (std::sin (currentAngle) * level);
     
                        for (auto i = outputBuffer.getNumChannels(); --i >= 0;)
                            outputBuffer.addSample (i, startSample, currentSample);
     
                        currentAngle += angleDelta;
                        ++startSample;
                    }
                }
            }
        }
        
    private:
        
        float currentAngle = 0.0f;
        float velocity = 0.f;
        float level = 0.f;
        float tailOff = 0.0f;
        float angleDelta = 0.f;
        
    };
    
    
    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (Synth_DemoAudioProcessor)
};
