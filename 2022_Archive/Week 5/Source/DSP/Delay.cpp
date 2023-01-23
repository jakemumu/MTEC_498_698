//
//  Delay.cpp
//  Course Plugin - Shared Code
//
//  Created by Jacob Penn on 2/22/22.
//

#include "Delay.h"

/* */
Delay::Delay()
{
    
}

/* */
Delay::~Delay()
{
    
}

/* */
void Delay::initialize(float inSampleRate)
{
    mSampleRate = inSampleRate;
    mCircularBuffer.setSize(1, 5 * inSampleRate);
}

/* */
void Delay::setParameters(float inTimeSeconds, float inFeedbackAmount, float inMix)
{
    mFeedbackAmount = inFeedbackAmount;
    mTimeInSeconds = inTimeSeconds;
    mMix = inMix;
}

/* */
void Delay::processBlock(float* inBuffer, int inNumSamples)
{
    for (int i = 0; i < inNumSamples; i++) {
        processSample(inBuffer[i]);
    }
}

/* */
void Delay::processSample(float& inSample)
{
    mCircularBuffer.setSample(0, mWriteHead, std::tanh(inSample + (mFeedbackSample * mFeedbackAmount)));
    
    mWriteHead++;
    
    if (mWriteHead >= mCircularBuffer.getNumSamples()) {
        mWriteHead = 0;
    }
    
    float time_in_sample = mTimeInSeconds * mSampleRate;
    float read_head = mWriteHead - time_in_sample;
    
    if (read_head < 0) {
        read_head += mCircularBuffer.getNumSamples();
    }
    
    float output_sample = mCircularBuffer.getSample(0, read_head);
    
    mFeedbackSample = output_sample;
    
    inSample = (output_sample * mMix) + (inSample * (1.f-mMix));
}
