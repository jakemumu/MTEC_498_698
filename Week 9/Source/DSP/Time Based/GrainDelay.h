//
//  GrainDelay.hpp
//  Course Plugin - Shared Code
//
//  Created by Jacob Penn on 4/10/23.
//

#ifndef GrainDelay_hpp
#define GrainDelay_hpp

#include "JuceHeader.h"
#include "RealTimeGranular.h"

class GrainDelay {
    
public:
    
    /* */
    GrainDelay();
    
    /* */
    ~GrainDelay();
    
    /* */
    void initialize(float inSampleRate, int inBlocksize);
    
    /* */
    void setParameters(float inTimeSeconds, float inFeedbackAmount, float inMix, float inLPFreq, float inHPFreq);
    
    /* */
    void processBlock(float* inBuffer, int inNumSamples);
    
    /* */
    void processSample(float& inSample);
    
private:
    
    RealTimeGranular mRealTimeGranulator;
    
    juce::LinearSmoothedValue<float> mTimeInSeconds;
    float mFeedbackAmount = 0;
    float mMix = 0;
    
    float mWriteHead = 0;
    float mFeedbackSample = 0;
    
    juce::AudioBuffer<float> mCircularBuffer;
        
    float mSampleRate;
    
    juce::dsp::IIR::Coefficients<float> mHighpassCoefficients;
    juce::dsp::IIR::Filter<float> mHighPassFilter;
    
    juce::dsp::IIR::Coefficients<float> mLowpassCoefficients;
    juce::dsp::IIR::Filter<float> mLowpassFilter;
};


#endif /* GrainDelay_hpp */
