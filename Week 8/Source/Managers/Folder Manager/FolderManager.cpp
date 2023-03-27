//
//  MKUFolderManager.cpp
//  Course Plugin - Shared Code
//
//  Created by Jacob Penn on 3/8/22.
//

#include "FolderManager.h"

FolderManager::FolderManager()
{

}

FolderManager::~FolderManager()
{
    
}

File FolderManager::getRootFolder()
{
    auto osType = SystemStats::getOperatingSystemType();
    File folder;
    
    if ((osType & SystemStats::MacOSX) != 0) {
        
        folder = File("/Library/Application Support/MTEC_PLUGS/");
        
    } else if ((osType & SystemStats::Windows) != 0) {
        
        folder = File::getSpecialLocation(File::commonApplicationDataDirectory).getChildFile("MTEC_PLUGS");
        
    }
    
    folder.getParentDirectory().setReadOnly(false);
    
    if (!folder.exists()) {
        DBG("Created Root Folder " + folder.createDirectory().getErrorMessage());
    }
    
    return folder;
}

File FolderManager::getAppFolder()
{
    File productAppFolder = getRootFolder().getChildFile(JucePlugin_Name);
    
    if (!productAppFolder.exists()) {
        DBG("Created Product Folder " + productAppFolder.createDirectory().getErrorMessage());
    }
    
    return productAppFolder;
}

File FolderManager::getPresetsFolder()
{
    File presetsFolder = getAppFolder().getChildFile("Presets");
    
    if (!presetsFolder.exists()) {
        DBG("Created Preset Folder " + presetsFolder.createDirectory().getErrorMessage());
    }
    
    return presetsFolder;
}
