//
//  ofxFBXNode.cpp
//  ofxFBX-Example-Importer
//
//  Created by Nick Hardeman on 10/31/13.
//
//

#include "ofxFBXNode.h"

//----------------------------------------
ofxFBXNode::ofxFBXNode( int level, const string & log_id ) {
//    parent          = NULL;
//    globalParent    = NULL;
    this->m_log_id = log_id;
    this->m_level = level;
}

//----------------------------------------
ofxFBXNode::~ofxFBXNode() {
    
}

//----------------------------------------
void ofxFBXNode::setup( FbxNode *pNode ) {
    setName( pNode->GetNameOnly() );
}

//----------------------------------------
string ofxFBXNode::getName() {
    return name;
}

//----------------------------------------
FbxString ofxFBXNode::getFbxName() {
    return FbxString( name.c_str() );
}

//----------------------------------------
void ofxFBXNode::setName( FbxString aName ) {
    name = aName;
}



