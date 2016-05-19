//
//  ofxFBXMesh.h
//  ofxFBX-Example-Importer
//
//  Created by Nick Hardeman on 10/31/13.
//
//


#pragma once

#define FBXSDK_NEW_API

//#if defined(TARGET_LINUX) && !defined(TARGET_OPENGLES)
//// Linux libs from Arturo Castro's ofxFBX -------
//// -- https://github.com/arturoc/ofxFBX --
//    #include <fbxsdk.h>
//#endif
//
//#include "ofMain.h"
//#if defined(TARGET_OSX)
//    #include "fbxsdk.h"
//#include "fbxscene.h"
//#endif

#include "ofMain.h"
#include <fbxsdk.h>

#include "ofxFBXUtils.h"
#include "ofxFBXAnimation.h"
#include "ofxFBXMesh.h"
#include "ofxFBXBone.h"
#include "ofxFBXMeshMaterial.h"
#include "ofxFBXCluster.h"
#include "ofxFBXSkeleton.h"
#include "ofxFBXPose.h"

#include "macro.h"

DEF_CLASS_SMART_PTR( ofxFBXScene )

#define ofxFBXSceneBEGIN CLOG( INFO, (this->_settings.log_id + "begin").c_str() ) << "";
#define ofxFBXSceneINFO CLOG( INFO, this->_settings.log_id.c_str() )
#define ofxFBXSceneWARN CLOG( WARNING, this->_settings.log_id.c_str() )
#define ofxFBXSceneERROR CLOG( ERROR, this->_settings.log_id.c_str() )
#define ofxFBXSceneBEGIN CLOG( INFO, (this->_settings.log_id + "begin").c_str() ) << "";
#define ofxFBXSceneEND CLOG( INFO, (this->_settings.log_id ).c_str() ) << "\n\n";

class ofxFBXSceneSettings {
public:
    ofxFBXSceneSettings() {
        importMaterials                 = true;
        importTextures                  = true;
        importBones                     = true; // bones /
        importShapes                    = true;
        importGobos                     = true;
        importAnimations                = true;
        log_id                          = "default";
    }
    
    bool importBones;
    bool importMaterials;
    bool importTextures;
    bool importShapes;
    bool importGobos;
    bool importAnimations;
    string log_id;
};


class ofxFBXScene{
public:
    
    ofxFBXScene();
    ~ofxFBXScene();
    
	bool load( const std::string & app_name, string path, ofxFBXSceneSettings aSettings = ofxFBXSceneSettings() );
    
    FbxScene* getFBXScene();
    
	vector< shared_ptr<ofxFBXMesh> >& getMeshes();
//    vector< shared_ptr<ofxFBXSkeleton> >& getSkeletons();
    
    
    int getNumAnimations();
    bool areAnimationsEnabled();
    void populateAnimations( vector<ofxFBXAnimation>& aInVector );
    
    void populateSkeletons( vector< shared_ptr<ofxFBXSkeleton> >& aInSkeletons );
    
    int getNumPoses();
    void populatePoses( vector< shared_ptr<ofxFBXPose> >& aInPoses );
    
    string getFbxFilePath();
    string getFbxFolderPath();

private:
    void cacheTexturesInScene( FbxScene* pScene, const std::string & app_name );
    void deleteCachedTexturesInScene( FbxScene* pScene );
    bool isValidTexturePath( string aPathToTexture );
    
    void cacheMaterialsRecursive( FbxNode* pNode );
    void deleteCachedMaterialsRecursive( FbxNode* pNode );
    
    void populateAnimationInformation();
    void populateCachedSkeletonAnimationInformation();
    void populateMeshesRecursive( FbxNode* pNode, FbxAnimLayer* pAnimLayer, int level );
    void populateBonesRecursive( FbxNode* pNode, FbxAnimLayer* pAnimLayer );
    void parentBonesRecursive( FbxNode* pNode, list<FbxNode*>& aSkeletonBases, int aBoneLevel );
    void constructSkeletons( FbxNode* pNode, FbxAnimLayer* pAnimLayer );
    void constructSkeletonsRecursive( ofxFBXSkeleton* aSkeleton, FbxNode* pNode, int aBoneLevel );
    
    mutable FbxTime mCache_Start, mCache_Stop;
    void PreparePointCacheData(FbxScene* pScene, FbxTime &pCache_Start, FbxTime &pCache_Stop);
    
    FbxTime fbxFrameTime;
    string fbxFilePath;
    
    vector< shared_ptr<ofxFBXBone> > bones;
    vector< shared_ptr<ofxFBXCluster> > clusters;
    
    vector< shared_ptr<ofxFBXMesh> > meshes;
    vector< shared_ptr<ofxFBXSkeleton> > skeletons;
	
    FbxManager* lSdkManager;
	FbxScene* lScene;
    
    vector<ofxFBXAnimation> animations;
    FbxAnimLayer* currentFbxAnimationLayer;
    
    ofxFBXSceneSettings _settings;
    
    std::string m_app_name;
};















