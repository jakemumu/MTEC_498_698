//
//  RealTimeGranular.h
//  Course Plugin
//
//  Created by Jacob Penn on 4/10/23.
//

#ifndef RealTimeGranular_h
#define RealTimeGranular_h

class RealTimeGranular {
public:
    
    /* */
    void prepareToPlay(int inSampleRate, int inBlockSize);
    
    /* */
    void process(float* inBufferLeft, float* inBufferRight, int inNumSamples);
    
private:
    
};

#endif /* RealTimeGranular_h */
