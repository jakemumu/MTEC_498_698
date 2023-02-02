#include "MainComponent.h"

//==============================================================================
MainComponent::MainComponent()
{
    // set the size of the window
    setSize (500, 500);
    
    // start the regular "update" function -- this will be 30 times a second
    startTimerHz(30);
}

MainComponent::~MainComponent()
{
}

//==============================================================================
void MainComponent::paint (juce::Graphics& g)
{
    // fill the background white
    g.fillAll(juce::Colours::white);

    // set the graphics context to red
    g.setColour(juce::Colours::red);
    
    // the size of our dot
    float dot_size = 4;
    
    // a horizontal line across the middle of the widow
    g.drawLine(0, getHeight()/2, getWidth(), getHeight()/2);
    
    // for every x pixel in our window, hop in groups of 6
    for (int x = 0; x < getWidth(); x += 6) {
        
        // calculate a "phase" for this part of the sine wave. 
        // For this example, the phase of the pixels will distribute 0 - 1
        float phase = (float)x / (float)getWidth();

        // we add the global phase to this value, this will create the speed
        // and animated effect -- try removing this to see how it changes things.
        phase += mGlobalPhase;
        
        // the height of our sine
        float offset_height = getHeight() * .25f;
        
        // the y offset for this position -- this will transform the range input: [0 - 1] -> [-1 - 1]
        float sin_y = sinf(phase * juce::MathConstants<float>::twoPi);
        
        // scale the offset
        float offset_y = offset_height * sin_y;
        
        // draw a line from the center to this point
        g.drawLine(x, getHeight()/2, x, getHeight()/2 + offset_y);
                
        // draw a circle at the point
        g.fillEllipse(x - dot_size/2.f, getHeight()/2 - dot_size/2.f + offset_y, dot_size, dot_size);
        
    }
}

void MainComponent::timerCallback()
{
    // move the sine wave
    mGlobalPhase += 0.005;

    // keep the phase controlled
    if (mGlobalPhase > 1.f) {
        mGlobalPhase -= 1.f;
    }

    // repaint
    repaint();
}
