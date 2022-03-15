/*
  ==============================================================================

    DBMeter.cpp
    Created: 15 Mar 2022 11:59:43am
    Author:  Jacob Penn

  ==============================================================================
*/

#include "DBMeter.h"
#include "ProcessorInterface.h"

/* */
DBMeter::DBMeter(ProcessorInterface* inInterface, bool inOutputMeter)
{
    mOutputMeter = inOutputMeter;
    mInterface = inInterface;
    startTimerHz(30);
}

/* */
DBMeter::~DBMeter()
{
    
}

/* */
void DBMeter::paint(Graphics& g)
{
    g.setColour(Colours::pink);
    g.fillAll();
    
    g.setColour(Colours::black);
    g.fillRect(0, (int)yPos, getWidth(), getHeight());
}

/* */
void DBMeter::resized()
{
    
}

void DBMeter::timerCallback()
{
    float new_amplitude = mInterface->getGain(mOutputMeter);
    
    if (new_amplitude > mCurrentAmplitudeValue) {
        mCurrentAmplitudeValue = new_amplitude;
    } else {
        mCurrentAmplitudeValue *= .75;
    }
    
    float db_value = Decibels::gainToDecibels(mCurrentAmplitudeValue);
    
    float max = 0;
    float min = -60;
    
    yPos = jmap(db_value, min, max, (float)getHeight(), 0.f);
    
    repaint();
}
