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
    GAIN_AMOUNT = 0,
    FM_AMOUNT,
    TotalNumberParameters
};

static const juce::StringArray PARAMETER_NAMES {
    "Gain Amount",
    "FM Amount",
};

/* the normaliseable range class will be helpful in the future when working with
   more complicated ranges (ones which aren't 0-1)
 */
static const juce::Array<juce::NormalisableRange<float>> PARAMETER_RANGES {
    // start value, end value, interval, skew/curve
    juce::NormalisableRange<float>(0.f, 1.f, 0.f, 1.f),
    juce::NormalisableRange<float>(0.f, 1.f, 0.f, 1.f),
};

#endif /* ParameterDefines_h */
