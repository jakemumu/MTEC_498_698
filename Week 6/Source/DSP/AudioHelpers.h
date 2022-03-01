//
//  AudioHelpers.h
//  Course Plugin
//
//  Created by Jacob Penn on 3/1/22.
//

#ifndef AudioHelpers_h
#define AudioHelpers_h

namespace AudioHelpers
{

inline float lin_interp(float sample_x, float sample_x1, float float_phase)
{
    return (1 - float_phase) * sample_x + float_phase * sample_x1;
}

};

#endif /* AudioHelpers_h */
