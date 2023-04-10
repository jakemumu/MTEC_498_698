//
//  SampleBase.cpp
//  GrainSynth - Shared Code
//
//  Created by Jacob Penn on 7/6/21.
//  Copyright © 2021 Minimal Audio. All rights reserved.
//

#include "SampleBase.h"
#include "AudioHelpers.h"

SampleBase::SampleBase()
{
    mFormatManager.registerBasicFormats();
    mFileLoaded = false;
}

SampleBase::~SampleBase()
{
    
}

//=======================
// === Base Functions ===
//=======================

bool SampleBase::loadFile(File inFile)
{
    AudioFormat* format = mFormatManager.findFormatForFileExtension(inFile.getFileExtension());
        
    if (inFile.exists() == false) {
        NativeMessageBox::showMessageBox(AlertWindow::NoIcon,
                                         "Unable To Open Locate File",
                                         inFile.getFileName());
        mFileLoaded = false;
        return false;
    }
    
    if (format == nullptr) {
        NativeMessageBox::showMessageBox(AlertWindow::NoIcon,
                                         "Unable To Open Format",
                                         inFile.getFileExtension());
        mFileLoaded = false;
        return false;
    }
            
    mFileReader.reset(mFormatManager.createReaderFor(inFile));
    
    if (mFileReader.get()) {
        
        mFile = inFile;
        mNumChannels = mFileReader->numChannels;
        mLengthInSamples = (int)mFileReader->lengthInSamples;
        mSampleRate = mFileReader->sampleRate;
        
        mZ1Results.resize(mNumChannels);
        mXResults.resize(mNumChannels);
        mX1Results.resize(mNumChannels);
        mX2Results.resize(mNumChannels);
        
        readerInitialized();
        
        mFileLoaded = true;
        return true;
        
    } else {
        
        NativeMessageBox::showMessageBox(AlertWindow::NoIcon,
                                         "Unknown Error Occured Opening File",
                                         mFile.getFileName());
        mFileLoaded = false;
        return false;
    }
}

int SampleBase::getLengthInSamples()
{
    return mLengthInSamples;
}

float SampleBase::getSampleRate()
{
    return mSampleRate;
}

int SampleBase::getNumChannels()
{
    return mNumChannels;
}

File SampleBase::getLoadedFile()
{
    return mFile;
}

bool SampleBase::isFileLoaded()
{
    return mFileLoaded;
}

AudioFormatManager* SampleBase::getFormantManager()
{
    return &mFormatManager;
}

AudioFormatReader* SampleBase::getFileReader()
{
    return mFileReader.get();
}

//========================
// === Reading Samples ===
//========================

void SampleBase::getLinearInterpolatedSample(float inFloatSample,
                                             std::vector<float>& inResults,
                                             bool inWrapPhases)
{
    int sample_x = (int)inFloatSample;
    int sample_x1 = sample_x + 1;
    float float_pos = inFloatSample - sample_x;
    
    if (inWrapPhases) {
        sample_x = (sample_x + (int)getLengthInSamples()) % getLengthInSamples();
        sample_x1 = (sample_x1 + (int)getLengthInSamples()) % getLengthInSamples();
    }
    
    getSample(sample_x, mXResults);
    getSample(sample_x1, mX1Results);
        
    if (mNumChannels == 1) {
        inResults[0] = AudioHelpers::lin_interp(mXResults[0], mX1Results[0], float_pos);
    } else if (mNumChannels == 2) {
        inResults[0] = AudioHelpers::lin_interp(mXResults[0], mX1Results[0], float_pos);
        inResults[1] = AudioHelpers::lin_interp(mXResults[1], mX1Results[1], float_pos);
    } else {
        jassert(false);
    }
}
