/*
  ==============================================================================

    Delay.cpp
    Created: 13 Feb 2023 5:12:49pm
    Author:  Jacob Penn

  ==============================================================================
*/

#include "Delay.h"

/* */
void Delay::setSampleRate(float inSampleRate)
{
    mSampleRate = inSampleRate;
    
    // 2 channel 10 second audio buffer
    mCircularBuffer.setSize(2, inSampleRate * 10);
}

///* */
//void Delay::setParameters(float inDelayTime, float inDelayFeedback)
//{
//
//}

/* */
void Delay::processSample(float& inSampleLeft, float& inSampleRight)
{
    // Step 1 - Write to the delay line.
    mCircularBuffer.setSample(0, mWriteHead, inSampleLeft);
    mCircularBuffer.setSample(1, mWriteHead, inSampleRight);
    
    // Step 2 - Calculate the read position based on the current delay time
    float delay_time_samples = mDelayTime * mSampleRate;
    int readhead = mWriteHead - delay_time_samples;
    
    
    // circular buffer wrap the readhead
    if (readhead < 0) {
        readhead += mCircularBuffer.getNumSamples();
    }
    
    
    // Step 3 - Read the & replace the input with the delayed signal
    inSampleLeft = mCircularBuffer.getSample(0, readhead);
    inSampleRight = mCircularBuffer.getSample(1, readhead);
    
    // circular buffer wrap the writehead
    mWriteHead++;
    
    if (mWriteHead >= mCircularBuffer.getNumSamples()) {
        mWriteHead = 0;
    }
}
