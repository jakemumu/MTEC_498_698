/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"
#include "UI/MyLookAndFeel.h"
#include "UI/DBMeter.h"

//==============================================================================
/**
*/
class CoursePluginAudioProcessorEditor  : public juce::AudioProcessorEditor,
                                          public juce::DragAndDropContainer
{
public:
    
    // We see our processor comes into this editor class throug it's constructor
    CoursePluginAudioProcessorEditor (CoursePluginAudioProcessor&);
    
    ~CoursePluginAudioProcessorEditor() override;

    
    /*
        The paint function is where we put our graphical code.
        
        It will be drawn when significant changes happen to the system,
     
        or manually when we call repaint() on this class.
     */
    void paint (juce::Graphics&) override;
    
    /*
        The resized function is for performing layout
        
        It will be called when the size of our component changes.
     */
    void resized() override;

private:
    
    class Draggable : public Component {
    public:
        /* */
        void paint(Graphics& g) override {
            g.fillAll(Colours::red);
        }
        /* */
        void mouseDown(const MouseEvent& e) override {
            juce::DragAndDropContainer* drag_container =
                    juce::DragAndDropContainer::findParentDragContainerFor(this);
            drag_container->startDragging("", this);
        }
        
    };
    
    Draggable mDraggableComponent;
    
    void _updatePresetComboBoxOptions();
        
    OwnedArray<Slider> mSliders;
    OwnedArray<AudioProcessorValueTreeState::SliderAttachment> mSliderAttachments;
    
    TextButton mSavePreset;
    ComboBox mPresetOptions;

    MyLookAndFeel mLookAndFeel;
    
    std::unique_ptr<DBMeter> mInputMeter;
    std::unique_ptr<DBMeter> mOutputMeter;
    
    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    CoursePluginAudioProcessor& audioProcessor;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (CoursePluginAudioProcessorEditor)
};
