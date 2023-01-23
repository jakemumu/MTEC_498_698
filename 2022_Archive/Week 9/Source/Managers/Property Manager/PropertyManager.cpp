/*
  ==============================================================================

    Property Manager.cpp
    Created: 15 Mar 2022 11:42:33am
    Author:  Jacob Penn

  ==============================================================================
*/

#include "PropertyManager.h"

/* */
PropertyManager::PropertyManager(ProcessorInterface* inInterface)
: mPropertyTree("Property Tree")
{
    mInterface = inInterface;
}

/* */
PropertyManager::~PropertyManager()
{
    
}

ValueTree& PropertyManager::getPropertyTree()
{
    return mPropertyTree;
}
