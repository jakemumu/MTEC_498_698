//
//  PresetManager.cpp
//  Course Plugin - Shared Code
//
//  Created by Jacob Penn on 3/8/22.
//

#include "PresetManager.h"
#include "ProcessorInterface.h"
#include "FolderManager.h"
#include "ParameterManager.h"

/* */
PresetManager::PresetManager(ProcessorInterface* inInterface)
: mProcessorInterface(inInterface)
{
    auto presetsFolder = FolderManager::getPresetsFolder();
}

/* */
PresetManager::~PresetManager()
{
    
}

/* */
void PresetManager::saveCurrentPreset(String inPresetName)
{
    // Get the underlying ValueTree from out "Parameter Value Tree"
    auto tree_state = mProcessorInterface->getParameterManager()->getValueTree()->copyState();
    
    // Convert the value tree into an XML object which can be saved on disk to as binary
    std::unique_ptr<juce::XmlElement> xml(tree_state.createXml());
    
    auto preset_file = FolderManager::getPresetsFolder().getChildFile(inPresetName+".xml");
    
    if (preset_file.existsAsFile()) {
        preset_file.deleteFile();
    }
    
    preset_file.appendText(xml->toString());
}
