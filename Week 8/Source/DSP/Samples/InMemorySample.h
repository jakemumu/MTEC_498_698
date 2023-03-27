//
//  InMemorySample.h
//  GrainSynth - Shared Code
//
//  Created by Jacob Penn on 7/6/21.
//  Copyright © 2021 Minimal Audio. All rights reserved.
//

#ifndef InMemorySample_h
#define InMemorySample_h

#include "SampleBase.h"

class InMemorySample : public SampleBase
{
public:
    
    /* */
    InMemorySample();
    
    /* */
    ~InMemorySample();
    
    /* */
    void readerInitialized() override;
    
    /* */
    void getSample(int64 inPosition, std::vector<float>& inResults) override;
    
    /* */
    void getSample(int64 inPositionLeft, int64 inPositionRight, std::vector<float>& inResults) override;
    
    /* */
    AudioBuffer<float>* getBuffer();
    
private:
    
    std::unique_ptr<AudioBuffer<float>> mInMemoryBuffer;

};

#endif /* InMemorySample_h */
