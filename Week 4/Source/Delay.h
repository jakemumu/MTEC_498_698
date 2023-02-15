/*
  ==============================================================================

    Delay.h
    Created: 13 Feb 2023 5:12:49pm
    Author:  Jacob Penn

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

class Delay {
    
public:
    
    /* */
    void setSampleRate(float inSampleRate);
    
//    /* */
//    void setParameters(float inDelayTime);
    
    /* */
    void processSample(float& inSampleLeft, float& inSampleRight);
    
private:
    
    float mDelayTime = 2.f;
    
    int mWriteHead = 0;
    
    float mSampleRate = 0;
    juce::AudioBuffer<float> mCircularBuffer;
};
