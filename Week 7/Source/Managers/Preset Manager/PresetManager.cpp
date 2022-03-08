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
    
    _constructPresetFilesArray();
}

/* */
PresetManager::~PresetManager()
{
    
}

/* */
void PresetManager::loadPreset(int inListIndex)
{
    auto file_to_load = mPresetFiles[inListIndex];
    
    std::unique_ptr<XmlElement> preset_xml(parseXML(file_to_load));
        
    juce::ValueTree parameter_tree = juce::ValueTree::fromXml(*preset_xml);
    mProcessorInterface->getParameterManager()->getValueTree()->replaceState(parameter_tree);
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
    
    _constructPresetFilesArray();
}

StringArray PresetManager::getCurrentPresetNames()
{
    StringArray preset_names;
    
    for (auto file : mPresetFiles) {
        preset_names.add(file.getFileNameWithoutExtension());
    }
    
    return preset_names;
}

void PresetManager::_constructPresetFilesArray()
{
    mPresetFiles.clear();
    
    RangedDirectoryIterator iter(FolderManager::getPresetsFolder(), false, "*.xml");
    
    for (auto entry : iter) {
        mPresetFiles.add(entry.getFile());
    }
}
