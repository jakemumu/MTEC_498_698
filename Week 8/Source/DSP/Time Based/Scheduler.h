//
//  Scheduler.h
//  Course Plugin
//
//  Created by Jacob Penn on 4/3/23.
//

#ifndef Scheduler_h
#define Scheduler_h

class Scheduler {
public:
    
    void setTime(int inTimeSamples) {
        mTimeInSamples = inTimeSamples;
    }
    
    bool trigger() {
        auto res = mCounter == 0;
        
        mCounter++;
        
        if (mCounter >= mTimeInSamples) {
            mCounter = 0;
        }
        
        return res;
    }
    
    void reset() {
        mCounter = 0;
    }
    
private:
    
    int mCounter = 0;
    int mTimeInSamples = 0;
};

#endif /* Scheduler_h */
