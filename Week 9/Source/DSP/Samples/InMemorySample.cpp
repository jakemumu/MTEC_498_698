//
//  InMemorySample.cpp
//  GrainSynth - Shared Code
//
//  Created by Jacob Penn on 7/6/21.
//  Copyright © 2021 Minimal Audio. All rights reserved.
//

#include "InMemorySample.h"

InMemorySample::InMemorySample()
{
    
}

InMemorySample::~InMemorySample()
{
    
}

void InMemorySample::readerInitialized()
{
    mInMemoryBuffer.reset(new AudioBuffer<float>(getNumChannels(), (int)getLengthInSamples()));
    getFileReader()->read(mInMemoryBuffer.get(), 0, (int)getLengthInSamples(), 0, true, true);
}

void InMemorySample::getSample(int64 inPosition, std::vector<float>& inResults)
{
    if (inPosition < 0 || inPosition >= getLengthInSamples()) {
        inResults[0] = 0;
        inResults[1] = 0;
    }
    
    if (getNumChannels() == 1) {
        
        inResults[0] = mInMemoryBuffer->getSample(0, (int)inPosition);
        inResults[1] = inResults[0];
        
    } else if (getNumChannels() == 2) {
        
        inResults[0] = mInMemoryBuffer->getSample(0, (int)inPosition);
        inResults[1] = mInMemoryBuffer->getSample(1, (int)inPosition);
        
    }
}

void InMemorySample::getSample(int64 inPositionLeft, int64 inPositionRight, std::vector<float>& inResults)
{
    if (inPositionLeft < 0 || inPositionLeft >= getLengthInSamples()) {
        inResults[0] = 0;
    } else {
        inResults[0] = mInMemoryBuffer->getSample(0, (int)inPositionLeft);
    }
    
    if (inPositionRight < 0 || inPositionRight >= getLengthInSamples()) {
        inResults[1] = 0;
    } else {
        
        if (getNumChannels() == 1) {
            
            inResults[1] = mInMemoryBuffer->getSample(0, (int)inPositionRight);
            
        } else if (getNumChannels() == 2) {
            
            inResults[1] = mInMemoryBuffer->getSample(1, (int)inPositionRight);
            
        }
    }
}

AudioBuffer<float>* InMemorySample::getBuffer()
{
    return mInMemoryBuffer.get();
}
