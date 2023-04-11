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

class Grain {
public:
    
    /* */
    void processSample(const GrainBuffer& inGrainBuffer, float& outLeft, float& outRight) {
        
        float val = getNextWindowSample();
        
        outLeft = inGrainBuffer.getSample(0, mGrainReadhead) * val;
        outRight = inGrainBuffer.getSample(1, mGrainReadhead) * val;
        
        mGrainReadhead++;
        
    }

    void setSize(int inGrainSize) {
        mGrainSize = inGrainSize;
        // this make it not active after a set size call.
        // could be more explicit
        mGrainCounter = mGrainSize;
    }
        
    void start(float inStartPosition, int inCircularBufferSize) {
        mGrainReadhead = jlimit((float)0, (float)inCircularBufferSize, inStartPosition - 1.f);
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
    float mGrainReadhead;
    
    // size in sample
    int mGrainSize  = 0;
    
    // position in sample
    int mGrainCounter = 0;
};


#endif /* Grain_hpp */
