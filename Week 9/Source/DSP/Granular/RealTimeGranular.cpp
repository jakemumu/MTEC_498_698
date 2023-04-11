//
//  RealTimeGranular.cpp
//  Course Plugin
//
//  Created by Jacob Penn on 4/10/23.
//

#include "RealTimeGranular.h"

/* */
void RealTimeGranular::prepareToPlay(int inSampleRate, int inBlockSize)
{
    for (int i = 0; i < mGrains.size(); i++) {
        mGrains[i].setSize(mGrainsizeSeconds * inSampleRate);
    }
    
    mGrainBuffer.setSize(10.f * inSampleRate);
    mScheduler.setTime(mGrainsizeSeconds / mGrainOverlapRate * inSampleRate);
    mScheduler.reset();
}

/* */
void RealTimeGranular::process(float* inBufferLeft, float* inBufferRight, int inNumSamples)
{
    for (int sample = 0; sample < inNumSamples; sample++) {
                
        mGrainBuffer.writeToBuffer(inBufferLeft[sample], inBufferRight[sample]);
        
        if (mScheduler.trigger()) {
            for (int j = 0; j < mGrains.size(); j++) {
                if (mGrains[j].isActive() == false) {
                    mGrains[j].start(mGrainBuffer.getWriteHead(), mGrainBuffer.getNumSamples());
                    break;
                }
            }
        }

        inBufferLeft[sample] = 0;
        inBufferRight[sample] = 0;
        
        float temp_left;
        float temp_right;
        
        for (int j = 0; j < mGrains.size(); j++) {
            if (mGrains[j].isActive()) {
                mGrains[j].processSample(mGrainBuffer, temp_left, temp_right);
                inBufferLeft[sample] += temp_left;
                inBufferRight[sample] += temp_right;
            }
        }
    }
}
