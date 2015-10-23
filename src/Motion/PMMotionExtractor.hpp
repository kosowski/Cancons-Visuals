//
//  PMMotionExtractor.hpp
//  PMCancons_Visuals
//
//  Created by Eduard Frigola on 16/10/15.
//
//

#ifndef PMMotionExtractor_hpp
#define PMMotionExtractor_hpp

#pragma once

#include <stdio.h>
#include "ofMain.h"
#include "ofxKinectFeatures.h"
#include "ofxOpenNI.h"

#define MAX_DEVICES 1

struct kinectElement{
    float x;
    float y;
    float z;
    float a;
};
struct kinectInfo{
    kinectElement leftHand_joint;
    kinectElement rightHand_joint;
    kinectElement head_joint;
    kinectElement torso_joint;
};

class PMMotionExtractor
{
public:
    PMMotionExtractor() {};
    ~PMMotionExtractor() {};
    void setup();
    void update();
    void draw(); //noexistirà?
    void exit();
    
private:
    ofTrueTypeFont font;
    ofxKinectFeatures kinectFeatures;
    ofxOpenNI kinectNI;
    bool hadUsers;
    kinectInfo kinectOut;
    
    ofEvent<kinectInfo> eventKinectInfo;
};

#endif /* PMMotionExtractor_hpp */