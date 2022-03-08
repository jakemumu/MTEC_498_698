//
//  PresetManager.h
//  Course Plugin - Shared Code
//
//  Created by Jacob Penn on 3/8/22.
//

#ifndef PresetManager_h
#define PresetManager_h

#include "JuceHeader.h"

class ProcessorInterface;

class PresetManager {
public:

    /* */
    PresetManager(ProcessorInterface* inInterface);

    /* */
    ~PresetManager();
    
    /* */
    StringArray getCurrentPresets();
    
    /* */
    void saveCurrentPreset(String inPresetName);

private:
    
    ProcessorInterface* mProcessorInterface;
};

#endif /* PresetManager_h */
