//
//  FolderManager.hpp
//  Course Plugin - Shared Code
//
//  Created by Jacob Penn on 3/8/22.
//

#ifndef MKUFolderManager_h
#define MKUFolderManager_h

#include "JuceHeader.h"

class FolderManager {
public:
    
    /* constructor */
    FolderManager();
    
    /* destructor */
    ~FolderManager();
    
    /* returns the company root folder
        THIS FOLDER MUST BE CREATED MANUALLY OR VIA INSTALLER
     */
    static File getRootFolder();
    
    /* returns the folder for the current app */
    static File getAppFolder();
    
    /* returns the preset folder for the current app */
    static File getPresetsFolder();
    
};

#endif /* MKUFolderManager_hpp */
