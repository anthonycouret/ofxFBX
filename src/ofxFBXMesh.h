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
//    #include <fbxsdk.h>
//#endif
//
//#include "ofMain.h"
//#if defined(TARGET_OSX)
//    #include "fbxsdk.h"
//#endif

#include "ofMain.h"
#include <fbxsdk.h>

#include "ofVboMesh.h"
#include "ofxFBXNode.h"
#include "ofxFBXBone.h"
#include "ofxFBXCluster.h"

#define ofxFBXMeshBEGIN CLOG( INFO, (this->m_log_id + "begin").c_str() ) << "";
#define ofxFBXMeshINFO CLOG( INFO, this->m_log_id.c_str() )
#define ofxFBXMeshWARN CLOG( WARNING, this->m_log_id.c_str() )
#define ofxFBXMeshERROR CLOG( ERROR, this->m_log_id.c_str() )
#define ofxFBXMeshEND CLOG( INFO, (this->m_log_id ).c_str() ) << "\n\n";

class ofxFBXSubMesh {
public:
    
    ofxFBXSubMesh() {
        triangleCount   = 0;
        indexOffset     = 0;
        totalIndices    = 0;
    }
    
    ~ofxFBXSubMesh() {
        
    }
    
    bool bRender;
    int triangleCount;
    int indexOffset;
    int totalIndices;
};

class ofxFBXMesh : public ofxFBXNode {
public:
	ofxFBXMesh( int level, const string & log_id );
	virtual ~ofxFBXMesh();
    
    void setup( FbxNode * pNode );
	void setFBXMesh( FbxMesh* lMesh );
    void configureMesh( ofMesh& aMesh );
    
    void updateMesh( ofMesh* aMesh, FbxTime& pTime, FbxAnimLayer * pAnimLayer, FbxPose* pPose  );

    int preDraw( ofMesh* aMesh );
    void subDraw( int index );
    void postDraw( int sub_meshes_count );
    
	void draw( ofMesh* aMesh );
    void drawNormals( ofMesh* aMesh, float length, bool bFaceNormals);
    
    FbxMesh* getFbxMesh() { return fbxMesh;}
    int getNumSubMeshes();
    int getNumMaterials();
    
    bool hasClusterDeformation();
    
	ofVbo& getVbo();
    ofMesh& getOFMesh();
    
    FbxUInt64 getFbxID() { return this->fbxMesh->GetNode()->GetUniqueID(); }
    //    std::string getFbxName() { string name( this->fbxMesh->GetNode()->GetNameOnly() ); return name; }
    FbxUInt64 getFbxParentID() { return this->fbxMesh->GetNode()->GetParent()->GetUniqueID(); }
    FbxString getFbxParentName() { return this->fbxMesh->GetNode()->GetParent()->GetNameOnly(); }

private:
    
    void computeBlendShapes( ofMesh* aMesh, FbxTime& pTime, FbxAnimLayer * pAnimLayer );
    void computeSkinDeformation( FbxAMatrix& pGlobalPosition, FbxTime& pTime, FbxAnimLayer * pAnimLayer, FbxVector4* pVertexArray, FbxVector4* pNormalsArray, FbxPose* pPose );
    void computeLinearDeformation(FbxAMatrix& pGlobalPosition,
                                  FbxMesh* pMesh,
                                  FbxTime& pTime,
                                  FbxVector4* pVertexArray,
                                  FbxPose* pPose,
                                  bool bNormals);
    void computeDualQuaternionDeformation(FbxAMatrix& pGlobalPosition,
                                          FbxMesh* pMesh,
                                          FbxTime& pTime,
                                          FbxVector4* pVertexArray,
                                          FbxPose* pPose,
                                          bool bNormals);
    void computeClusterDeformation(FbxAMatrix& pGlobalPosition,
                                   FbxMesh* pMesh,
                                   FbxCluster* pCluster,
                                   FbxAMatrix& pVertexTransformMatrix,
                                   FbxTime pTime,
                                   FbxPose* pPose,
                                   bool bNormals);
    
    void ReadVertexCacheData(FbxMesh* pMesh,
                             FbxTime& pTime,
                             FbxVector4* pVertexArray);
    
    void populateNormals( FbxVector4* pNormalsArray );
    
    vector<ofxFBXSubMesh> subMeshes;
    ofVbo veebs;
	ofMesh mesh;
	ofMesh original;
	FbxMesh* fbxMesh;
    FbxVector4* mNormalsArray;
    bool bAllMappedByControlPoint;
};

