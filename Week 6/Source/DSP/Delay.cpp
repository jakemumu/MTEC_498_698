//
//  Delay.cpp
//  Course Plugin - Shared Code
//
//  Created by Jacob Penn on 2/22/22.
//

#include "Delay.h"
#include "AudioHelpers.h"

/* */
Delay::Delay()
{
    
}

/* */
Delay::~Delay()
{
    
}

/* */
void Delay::initialize(float inSampleRate, int inBlocksize)
{
    mSampleRate = inSampleRate;
    mCircularBuffer.setSize(1, 5 * inSampleRate);
    mTimeInSeconds.reset(inSampleRate, 0.25);
    mTimeInSeconds.setCurrentAndTargetValue(0.01);
    
    juce::dsp::ProcessSpec spec;
    spec.sampleRate = inSampleRate;
    spec.maximumBlockSize = inBlocksize;
    spec.numChannels = 1;
    
    mHighPassFilter.prepare(spec);
    mHighPassFilter.coefficients = mHighpassCoefficients.makeHighPass(inSampleRate, 10000);
}

/* */
void Delay::setParameters(float inTimeSeconds, float inFeedbackAmount, float inMix)
{
    mTimeInSeconds.setTargetValue(inTimeSeconds);
    mFeedbackAmount = inFeedbackAmount;
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
    
    float time_in_sample = mTimeInSeconds.getNextValue() * mSampleRate;
    float read_head = mWriteHead - time_in_sample;
    
    if (read_head < 0) {
        read_head += mCircularBuffer.getNumSamples();
    }
    
    // Get Interpolation Positions
    int sample_x_pos = floor(read_head);
    int sample_x1_pos = (sample_x_pos + 1) % mCircularBuffer.getNumSamples();
    float inter_sample_amount = read_head - sample_x_pos;
    
    // Get Interpolation Values
    float sample_x = mCircularBuffer.getSample(0, sample_x_pos);
    float sample_x1 = mCircularBuffer.getSample(0, sample_x1_pos);
    float output_sample = AudioHelpers::lin_interp(sample_x, sample_x1, inter_sample_amount);
    
    mFeedbackSample = output_sample;
    
    mFeedbackSample = mHighPassFilter.processSample(mFeedbackSample);
    
    output_sample = tanh(output_sample * 2);
    
    inSample = (output_sample * mMix) + (inSample * (1.f-mMix));
}
