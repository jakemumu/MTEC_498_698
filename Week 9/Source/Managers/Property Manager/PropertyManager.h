/*
  ==============================================================================

    Property Manager.h
    Created: 15 Mar 2022 11:42:33am
    Author:  Jacob Penn

  ==============================================================================
*/

#pragma once

#include "JuceHeader.h"

class ProcessorInterface;

class PropertyManager {
public:

    /* */
    PropertyManager(ProcessorInterface* inInterface);

    /* */
    ~PropertyManager();
    
    /* */
    ValueTree& getPropertyTree();
    
private:
    
    ValueTree mPropertyTree;
    
    ProcessorInterface* mInterface;
};
