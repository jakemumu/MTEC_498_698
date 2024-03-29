//
//  Grain.hpp
//  Course Plugin - Shared Code
//
//  Created by Jacob Penn on 4/3/23.
//

#ifndef Grain_h
#define Grain_h

#include "JuceHeader.h"
#include "GrainBuffer.h"
#include "AudioHelpers.h"

class Grain {
public:
    
    /* */
    void processSample(const GrainBuffer& inGrainBuffer, float& outLeft, float& outRight) {
        
        float val = getNextWindowSample();
        
        outLeft = inGrainBuffer.getSample(0, mGrainReadhead) * val;
        outRight = inGrainBuffer.getSample(1, mGrainReadhead) * val;
        
        mGrainReadhead += 2.f;
        
        mGrainReadhead = AudioHelpers::wrap_buffer(mGrainReadhead, inGrainBuffer.getNumSamples());
    }

    void setSize(int inGrainSize) {
        mGrainSize = inGrainSize;
        // this make it not active after a set size call.
        // could be more explicit
        mGrainCounter = mGrainSize;
    }
        
    void start(float inStartPosition, int inCircularBufferSize) {
        float distance_past_write = (mPitch - 1.f) * mGrainSize;
        
        mGrainReadhead = inStartPosition;
        mGrainReadhead = AudioHelpers::wrap_buffer(mGrainReadhead - distance_past_write, inCircularBufferSize);
        mGrainCounter = 0;
    }
    
    float getNextWindowSample() {
        if (isActive()) {
            mGrainCounter++;
                        
            return 0.5f * (1.0f - cos(juce::MathConstants<float>::twoPi * (float)mGrainCounter / (float)mGrainSize));
        } else {
            return 0;
        }
    }
    
    bool isActive() {
        if (mGrainCounter < mGrainSize) {
            return true;
        } else {
            return false;
        }
    }
    
private:
    
    // where to read from in the buffer
    float mGrainReadhead = 0.f;
    
    // size in sample
    int mGrainSize  = 0;
    
    // position in sample
    int mGrainCounter = 0;
    
    // up one octave
    float mPitch = 2.f;
};


#endif /* Grain_hpp */
