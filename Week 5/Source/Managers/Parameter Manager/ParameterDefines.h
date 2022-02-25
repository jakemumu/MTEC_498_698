//
//  ParameterDefines.h
//  Course Plugin
//
//  Created by Jacob Penn on 2/15/22.
//

#ifndef ParameterDefines_h
#define ParameterDefines_h

#include "JuceHeader.h"

// Course Plugin Parameter Defines

enum {
    SINE_GAIN = 0,
    SINE_FM_AMOUNT,
    SINE_FM_FREQUENCY,
    DELAY_TIME_SECONDS,
    DELAY_FEEDBACK,
    DELAY_MIX,
    TotalNumberParameters
};

static const juce::StringArray PARAMETER_NAMES {
    "Gain Amount",
    "FM Amount",
    "FM Frequency",
    "Delay Time Seconds",
    "Delay Feedback",
    "Delay Mix",
};

/* the normaliseable range class will be helpful in the future when working with
   more complicated ranges (ones which aren't 0-1)
 */
static const juce::Array<juce::NormalisableRange<float>> PARAMETER_RANGES {
    // start value, end value, interval, skew/curve
    juce::NormalisableRange<float>(0.f, 1.f, 0.f, 1.f),
    juce::NormalisableRange<float>(0.f, 1.f, 0.f, 1.f),
    juce::NormalisableRange<float>(1.f, 20000.f, 0.f, .25f),
    // 20 ms to 1 second
    juce::NormalisableRange<float>(.02f, 1.f, 0.f, 1.f),
    juce::NormalisableRange<float>(0.f, .9f, 0.f, 1.f),
    juce::NormalisableRange<float>(0.f, 1.f, 0.f, 0.5f),
};

#endif /* ParameterDefines_h */
