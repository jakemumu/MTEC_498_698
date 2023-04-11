//
//  RealTimeGranular.h
//  Course Plugin
//
//  Created by Jacob Penn on 4/10/23.
//

#ifndef RealTimeGranular_h
#define RealTimeGranular_h

#include "Grain.h"
#include "GrainBuffer.h"
#include "Scheduler.h"

class RealTimeGranular {
public:
    
    /* */
    void prepareToPlay(int inSampleRate, int inBlockSize);
    
    /* */
    void process(float* inBufferLeft, float* inBufferRight, int inNumSamples);
    
private:
    
    const float mGrainsizeSeconds = 0.1f;
    const float mGrainOverlapRate = 2.f;
    
    Scheduler mScheduler;
    GrainBuffer mGrainBuffer;
    std::array<Grain, 10> mGrains;
};

#endif /* RealTimeGranular_h */
