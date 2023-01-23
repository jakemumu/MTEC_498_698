/*
  ==============================================================================

    DBMeter.h
    Created: 15 Mar 2022 11:59:43am
    Author:  Jacob Penn

  ==============================================================================
*/

#pragma once

#include "JuceHeader.h"

class ProcessorInterface;

class DBMeter : public Component,
                public Timer
{
public:
    
    /* */
    DBMeter(ProcessorInterface* inInterface, bool inOutputMeter);
    
    /* */
    ~DBMeter();
    
    /* */
    void paint(Graphics& g) override;
    
    /* */
    void resized() override;
    
    /* */
    void timerCallback() override;

private:
    
    float mCurrentAmplitudeValue = 0;
    float yPos = 0;
    bool mOutputMeter = false;
    ProcessorInterface* mInterface;
};
