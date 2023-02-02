#pragma once

#include <JuceHeader.h>

//==============================================================================
/*
    This component lives inside our window, and this is where you should put all
    your controls and content.
*/
class MainComponent  : public juce::Component,
                       public juce::Timer
{
public:
    
    /* CONSTRUCTOR - This runs when a class gets constructed or built or used, etc.. in C++ */
    MainComponent();
    
    /* DESCTRUCTOR - This runs when a class gets deleted, goes out of scope, stops being used, etc.. in C++ */
    ~MainComponent() override;

    /* Paint - Inherited from juce::Component, and give us a graphic object to use for drawing */
    void paint (juce::Graphics&) override;
        
    /* Timer callback - Inherited from juce::Timer, gives us a regularly called function */
    void timerCallback() override;

private:
    
    // the global time / phase of the animation
    float mGlobalPhase = 0;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MainComponent)
};
