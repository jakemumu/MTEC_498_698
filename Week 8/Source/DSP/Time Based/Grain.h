//
//  Grain.hpp
//  Course Plugin - Shared Code
//
//  Created by Jacob Penn on 4/3/23.
//

#ifndef Grain_h
#define Grain_h


class Grain {
public:
    
    void setSize(int inGrainSize) {
        mGrainSize = inGrainSize;
    }
    
    void reset() {
        mGrainCounter = 0;
    }
    
    float getNextWindowSample() {
        mGrainCounter++;
        
        auto val = 0.5 * (1 - std::cos(6.283185307179586 * (float)mGrainCounter / (((float)mGrainSize)-1.f)));
        
        return val;
    }
    
    bool isActive() {
        if (mGrainCounter < mGrainSize) {
            return true;
        } else {
            return false;
        }
    }
    
private:
    
    // size in sample
    int mGrainSize  = 0;
    
    // position in sample
    int mGrainCounter = 0;
};


#endif /* Grain_hpp */
