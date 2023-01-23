/*
  ==============================================================================

    MyLookAndFeel.h
    Created: 1 Mar 2022 12:36:30pm
    Author:  Jacob Penn

  ==============================================================================
*/

#pragma once

#include "JuceHeader.h"

using namespace juce;

class MyLookAndFeel : public LookAndFeel_V4
{
public:
    
    /* */
    MyLookAndFeel();
    
    /* */
    ~MyLookAndFeel();
    
    /* */
    void drawRotarySlider(Graphics& g, int x, int y, int width, int height, float sliderPos,
                          const float rotaryStartAngle, const float rotaryEndAngle, Slider& slider) override;
    
private:
    
};
