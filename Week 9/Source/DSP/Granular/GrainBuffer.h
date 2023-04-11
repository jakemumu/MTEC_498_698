//
//  GrainBuffer.h
//  Course Plugin
//
//  Created by Jacob Penn on 4/3/23.
//

#ifndef GrainBuffer_h
#define GrainBuffer_h

#include "JuceHeader.h"

class GrainBuffer {
public:
    
    void setSize(int numSamples) {
        mCircularBuffer.setSize(2, numSamples);
    }
    
    void writeToBuffer(float& inLeft, float& inRight) {
//        DBG("WRITING LEFT: " << inLeft << " POSITION: " << mWriteHead);
//        DBG("WRITING RIGHT: " << inRight << " POSITION: " << mWriteHead);

        mCircularBuffer.setSample(0, mWriteHead, inLeft);
        mCircularBuffer.setSample(1, mWriteHead, inRight);
        
        mWriteHead++;
        
        if (mWriteHead >= mCircularBuffer.getNumSamples()) {
            mWriteHead = 0;
        }
    }
    
    float getSample(int inChannel, int inSample) const {
//        DBG("READING: " << inChannel << " - " << mCircularBuffer.getSample(inChannel, inSample) << " POSITION: " << mWriteHead);
        return mCircularBuffer.getSample(inChannel, inSample);
        
    }
    
    int getWriteHead() {
        return mWriteHead;
    }
    
    int getNumSamples() {
        return mCircularBuffer.getNumSamples();
    }
    
private:
    
    int mWriteHead = 0;
    
    AudioBuffer<float> mCircularBuffer;
    
};

#endif /* GrainBuffer_h */
