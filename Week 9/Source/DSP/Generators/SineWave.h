//
//  SineWave.h
//  Course Plugin - Shared Code
//
//  Created by Jacob Penn on 2/10/22.
//

#ifndef SineWave_h
#define SineWave_h

#include "JuceHeader.h"

/* THIS IS A BASIC SINEWAVE CLASS */

class SineWave {
    
// Public indicates that these methods will be available to the outside program
    
// ex SineWave.initialize(554, 44100)
public:
    
    /* CONSTRUCTOR
     
     A constructor is called when a class is created, it can be used to allocate memory
     or setup various internal data of the class
     
     */
    SineWave();
    
    
    /* DECONSTRUCTOR
     
     A deconstructor is called when a class is delete, it can be used to free memory
     or delete things we'll no longer be using in the application
     
     */
    ~SineWave();
    
    /* INITALIZE
     
     We call this initialze function from our prepare to play method to get our
     SineWave ready for playback
     
     */
    void initialize(float inFrequencyHz, float inSampleRate);
    
    /* getNextSample
     
     We call this every sample in order to get the next audio sample for our buffers output
     
     */
    float getNextSample();
    
    /* getNextSample w/ FM */
    float getNextSampleWithFM(float inFMOperator);
    
    /* */
    void setParameters(float inFreq, float inGain);
    
    
// Private means these are not accessible to the outside world
    
// ex: SineWave.mFreqHz <- Illegal and impossible to access a private member variable
private:
    
    // These are member variables of the class (internal data)
    float mFreqHz = 442;
    float mSampleRate = 44100;
    float mPhase = 0;
    
    juce::LinearSmoothedValue<float> mSmoothedGain;
};

#endif /* SineWave_h */
