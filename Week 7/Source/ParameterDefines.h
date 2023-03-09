/*
  ==============================================================================

    ParameterDefines.h
    Created: 6 Mar 2023 5:07:21pm
    Author:  Jacob Penn

  ==============================================================================
*/

#pragma once

enum AppParameterID {
    Mix = 0,
    Time,
    Feedback,
    Lowpass,
    Highpass,
    TotalNumberParameters
};

static juce::Array<juce::String> ParameterIDStrings {
    "Mix",
    "Time",
    "Feedback",
    "Lowpass",
    "Highpass"
};

static juce::Array<float> ParameterMinimum {
    0.f,
    .1f,
    0.f,
    20.f,
    20.f
};

static juce::Array<float> ParameterMaximum {
    1.f,
    1.f,
    .95f,
    22000.f,
    22000.f
};

static juce::Array<float> ParameterDefault {
    .5f,
    .5f,
    .5f,
    22000.f,
    20.f
};
