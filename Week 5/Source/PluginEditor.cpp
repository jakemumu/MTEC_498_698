/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"
#include "ParameterDefines.h"

//==============================================================================
CoursePluginAudioProcessorEditor::CoursePluginAudioProcessorEditor (CoursePluginAudioProcessor& p)
    : AudioProcessorEditor (&p), audioProcessor (p)
{
    // Lets set the properties we want to initialize on the slider.
    // Dont forget you can right click the name of classes, and select jump to
    // definition in order to see their available functions you can call.
    
    mGainAmountSlider.setSliderStyle(juce::Slider::SliderStyle::RotaryVerticalDrag);
    mGainAmountSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 150, 20);
    addAndMakeVisible(mGainAmountSlider);
    
    mFMAmountSlider.setSliderStyle(juce::Slider::SliderStyle::RotaryVerticalDrag);
    mFMAmountSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 150, 20);
    addAndMakeVisible(mFMAmountSlider);
    
    mFMFreqSlider.setSliderStyle(juce::Slider::SliderStyle::RotaryVerticalDrag);
    mFMFreqSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 150, 20);
    addAndMakeVisible(mFMFreqSlider);
    
    mDelayTimeSecondsSlider.setSliderStyle(juce::Slider::SliderStyle::RotaryVerticalDrag);
    mDelayTimeSecondsSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 150, 20);
    addAndMakeVisible(mDelayTimeSecondsSlider);
    
    mDelayFeedbackSlider.setSliderStyle(juce::Slider::SliderStyle::RotaryVerticalDrag);
    mDelayFeedbackSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 150, 20);
    addAndMakeVisible(mDelayFeedbackSlider);
    
    mDelayMixSlider.setSliderStyle(juce::Slider::SliderStyle::RotaryVerticalDrag);
    mDelayMixSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 150, 20);
    addAndMakeVisible(mDelayMixSlider);
    
    // Instead of using the lambda we used before -- we'll use this JUCE helper class which
    // connects our slider directly to our parameter tree -- previously we were treating gain as a
    // "property" -- the lambda is how to connect to those, now we're using parameters -- we can use
    // the slider attachments for those.
    
    typedef juce::AudioProcessorValueTreeState::SliderAttachment SliderAttachment;
    auto* value_tree = audioProcessor.getParameterManager()->getValueTree();
    
    mGainAmountSliderAttachment.reset(new SliderAttachment(*value_tree, PARAMETER_NAMES[SINE_GAIN], mGainAmountSlider));
    mFMAmountSliderAttachment.reset(new SliderAttachment(*value_tree, PARAMETER_NAMES[SINE_FM_AMOUNT], mFMAmountSlider));
    mFMFreqSliderAttachment.reset(new SliderAttachment(*value_tree, PARAMETER_NAMES[SINE_FM_FREQUENCY], mFMFreqSlider));
    mDelayTimeSecondsSliderAttachment.reset(new SliderAttachment(*value_tree, PARAMETER_NAMES[DELAY_TIME_SECONDS], mDelayTimeSecondsSlider));
    mDelayFeedbackSliderAttachment.reset(new SliderAttachment(*value_tree, PARAMETER_NAMES[DELAY_FEEDBACK], mDelayFeedbackSlider));
    mDelayMixSliderAttachment.reset(new SliderAttachment(*value_tree, PARAMETER_NAMES[DELAY_MIX], mDelayMixSlider));
    
    setSize(400, 300);
}

CoursePluginAudioProcessorEditor::~CoursePluginAudioProcessorEditor()
{
}

//==============================================================================
void CoursePluginAudioProcessorEditor::paint(juce::Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    
    g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));
    
    g.setColour(juce::Colours::white);
    g.setFont(juce::Font(12));
    g.drawSingleLineText("Gain", mGainAmountSlider.getX(), mGainAmountSlider.getBottom()+12);
    g.drawSingleLineText("FM Amount", mFMAmountSlider.getX(), mFMAmountSlider.getBottom()+12);
    g.drawSingleLineText("FM Freq", mFMFreqSlider.getX(), mFMFreqSlider.getBottom()+12);
    g.drawSingleLineText("Delay Time", mDelayTimeSecondsSlider.getX(), mDelayTimeSecondsSlider.getBottom()+12);
    g.drawSingleLineText("Delay Feedback", mDelayFeedbackSlider.getX(), mDelayFeedbackSlider.getBottom()+12);
    g.drawSingleLineText("Delay Mix", mDelayMixSlider.getX(), mDelayMixSlider.getBottom()+12);
}

void CoursePluginAudioProcessorEditor::resized()
{
    mGainAmountSlider.setBounds(0, 0, 75, 75);
    mFMAmountSlider.setBounds(100, 0, 75, 75);
    mFMFreqSlider.setBounds(200, 0, 75, 75);
    mDelayTimeSecondsSlider.setBounds(0, 87, 75, 75);
    mDelayFeedbackSlider.setBounds(100, 87, 75, 75);
    mDelayMixSlider.setBounds(200, 87, 75, 75);
}
