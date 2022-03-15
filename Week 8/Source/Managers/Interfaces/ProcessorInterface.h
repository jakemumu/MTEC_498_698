//
//  ProcessorInterface.h
//  Course Plugin
//
//  Created by Jacob Penn on 3/8/22.
//

#ifndef ProcessorInterface_h
#define ProcessorInterface_h

#include "JuceHeader.h"

class ParameterManager;
class PresetManager;
class PropertyManager;

class ProcessorInterface {
    
public:
    
    virtual ~ProcessorInterface() {};
    
    virtual ParameterManager* getParameterManager() = 0;
    
    virtual PresetManager* getPresetManager() = 0;
    
    virtual PropertyManager* getPropertyManager() = 0;
    
    virtual AudioProcessor* getAudioProcessor() = 0;
        
};

#endif /* ProcessorInterface_h */
