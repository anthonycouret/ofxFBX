//
//  ofxFBXMeshMaterial.h
//  ofxFBX-Example-Importer
//
//  Created by Nick Hardeman on 10/31/13.
//
//

#pragma once


//#if defined(TARGET_LINUX) && !defined(TARGET_OPENGLES)
//    #include <fbxsdk.h>
//#endif

#include "ofMain.h"
#include <fbxsdk.h>

#include "ogfTexture.hpp"

//#if defined(TARGET_OSX)
//    #include "fbxsdk.h"
//#endif

class ofxFBXMeshMaterial : public ofMaterial {
public:
    ofxFBXMeshMaterial();
    ~ofxFBXMeshMaterial() {}
    
    void setup( const FbxSurfaceMaterial * pMaterial, const std::string & app_name );
    
    void begin();
    void end();
    
    bool hasTexture();
    ogfTextureShPtr getTextureShPtr();
    void enableTextures();
    void disableTextures();
    bool areTexturesEnabled();
    
    void enableMaterials();
    void disableMaterials();
    bool areMaterialsEnabled();
    
    void enable();
    void disable();
    bool isEnabled();
    
    string getName();
    string getInfoAsString();
    
    // from ViewScene example included in the SDK //
    // Get specific property value and connected texture if any.
    // Value = Property value * Factor property value (if no factor property, multiply by 1).
    static ofFloatColor getMaterialProperty(const FbxSurfaceMaterial * pMaterial,
                                     const char * pPropertyName,
                                     const char * pFactorPropertyName );
    
protected:
    bool findTextureForProperty(const FbxSurfaceMaterial * pMaterial,
                                const char * pPropertyName,
                                const std::string & app_name );
    
    bool _bTexturesEnabled;
    bool _bMaterialsEnabled;
    bool _bEnabled;
    string _name;
    ogfTextureShPtr texture;
    
};





