//
//  SampleBase.h
//  GrainSynth - Shared Code
//
//  Created by Jacob Penn on 7/6/21.
//  Copyright © 2021 Minimal Audio. All rights reserved.
//

#ifndef SampleBase_h
#define SampleBase_h

#include "JuceHeader.h"

class SampleBase
{
public:
    
    /* */
    SampleBase();
    
    /* */
    virtual ~SampleBase();
    
    //=================
    // === Virtuals ===
    //=================

    /* Initialize how you want to handle the sample here */
    virtual void readerInitialized() = 0;
    
    /* Returns the samples at this position here */
    virtual void getSample(int64 inPosition, std::vector<float>& inResults) = 0;
    virtual void getSample(int64 inPositionLeft, int64 inPositionRight, std::vector<float>& inResults) = 0;
    
    //=======================
    // === Base Functions ===
    //=======================
    
    /* */
    bool loadFile(File inFile);
    
    /* */
    File getLoadedFile();
    
    /* */
    bool isFileLoaded();
    
    /* */
    int getLengthInSamples();
    
    /* */
    float getSampleRate();
    
    /* */
    int getNumChannels();
    
    /* */
    AudioFormatManager* getFormantManager();
    
    /* */
    AudioFormatReader* getFileReader();
    
    //========================
    // === Reading Samples ===
    //========================
    
    /* */
    void getLinearInterpolatedSample(float inFloatSample,
                                     std::vector<float>& inResults,
                                     bool inWrapPhases);
    
private:
    
    File mFile;
        
    bool mFileLoaded;
    int mNumChannels;
    float mSampleRate;
    int mLengthInSamples;
    
    AudioFormatManager mFormatManager;
    std::unique_ptr<AudioFormatReader> mFileReader;
    
    /* Interpolation Samples */
    std::vector<float> mZ1Results;
    std::vector<float> mXResults;
    std::vector<float> mX1Results;
    std::vector<float> mX2Results;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(SampleBase)
};

#endif /* SampleBase_h */
