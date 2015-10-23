//
//  PMMotionExtractor.cpp
//  PMCancons_Visuals
//
//  Created by Eduard Frigola on 16/10/15.
//
//

#include "PMMotionExtractor.hpp"


///--------------------------------------------------------------
void PMMotionExtractor::setup()
{
    kinectNI.setup();
    kinectNI.addDepthGenerator();
    kinectNI.addImageGenerator();
    kinectNI.setRegister(false);
    kinectNI.setMirror(true);
    kinectNI.addUserGenerator();
    kinectNI.setMaxNumUsers(1);
    kinectNI.setSkeletonProfile(XN_SKEL_PROFILE_ALL);
    //kinectNI.addHandsGenerator();
    //kinectNI.addUserGenerator();
    //kinectNI.addAllHandFocusGestures();
    //kinectNI.setMaxNumHands(2);
    kinectNI.start();
    
    //ofSetWindowShape(640, 480);
    
    font.loadFont("verdana.ttf", 18);
    
    //ofAddListener(kinectNI.userEvent, this, &ofApp::userEvent);
}

///--------------------------------------------------------------
void PMMotionExtractor::update()
{
    kinectNI.update();
    for (int i = 0; i < kinectNI.getNumTrackedUsers(); i++) {
        ofxOpenNIUser user = kinectNI.getTrackedUser(i);
        //The following "if" statement is a hard-coded alternative for if(kinectNI.getUserGenerator().IsNewDataAvailable()), which doesn't work properly in ofxOpenNI
        if (user.getJoint((Joint)0).getWorldPosition() != ofPoint(0,0,0) &&
            user.getJoint((Joint)0).getWorldPosition() != kinectFeatures.getPosition(0) ) {
            map<int, ofPoint> joints;
            for (int j = 0; j < user.getNumJoints(); j++) {
                joints[j] = user.getJoint((Joint)j).getWorldPosition();
            }
            kinectFeatures.update(joints);
        }
    }
    
    //This is a trick to reset the user generator if all users are lost
    if (kinectNI.getNumTrackedUsers()) {
        hadUsers = true;
    } else if (!kinectNI.getNumTrackedUsers() && hadUsers){
        hadUsers = false;
        kinectNI.setPaused(true);
        kinectNI.removeUserGenerator();
        kinectNI.addUserGenerator();
        kinectNI.setPaused(false);
    }
    
    //wraper to kinectInfo struct
    kinectOut.leftHand_joint.x=kinectNI.worldToProjective(kinectFeatures.getPosition(JOINT_LEFT_HAND)).x/kinectNI.getWidth();
    kinectOut.leftHand_joint.y=kinectNI.worldToProjective(kinectFeatures.getPosition(JOINT_LEFT_HAND)).y/kinectNI.getHeight();
    kinectOut.leftHand_joint.z=ofMap(kinectNI.worldToProjective(kinectFeatures.getPosition(JOINT_LEFT_HAND)).z, 1000, 3000, 0, 1);
    kinectOut.leftHand_joint.a=(kinectFeatures.getAcceleration(JOINT_LEFT_HAND).y+kinectFeatures.getAcceleration(JOINT_LEFT_HAND).x)/2;
    kinectOut.rightHand_joint.x=kinectNI.worldToProjective(kinectFeatures.getPosition(JOINT_RIGHT_HAND)).x/kinectNI.getWidth();
    kinectOut.rightHand_joint.y=kinectNI.worldToProjective(kinectFeatures.getPosition(JOINT_RIGHT_HAND)).y/kinectNI.getHeight();
    kinectOut.rightHand_joint.z=ofMap(kinectNI.worldToProjective(kinectFeatures.getPosition(JOINT_RIGHT_HAND)).z, 1000, 3000, 0, 1);
    kinectOut.rightHand_joint.a=(kinectFeatures.getAcceleration(JOINT_RIGHT_HAND).y+kinectFeatures.getAcceleration(JOINT_RIGHT_HAND).x)/2;
    kinectOut.head_joint.x=kinectNI.worldToProjective(kinectFeatures.getPosition(JOINT_HEAD)).x/kinectNI.getWidth();
    kinectOut.head_joint.y=kinectNI.worldToProjective(kinectFeatures.getPosition(JOINT_HEAD)).y/kinectNI.getHeight();
    kinectOut.head_joint.z=ofMap(kinectNI.worldToProjective(kinectFeatures.getPosition(JOINT_HEAD)).z, 1000, 3000, 0, 1);
    kinectOut.head_joint.a=(kinectFeatures.getAcceleration(JOINT_HEAD).y+kinectFeatures.getAcceleration(JOINT_HEAD).x)/2;
    kinectOut.torso_joint.x=kinectNI.worldToProjective(kinectFeatures.getPosition(JOINT_TORSO)).x/kinectNI.getWidth();
    kinectOut.torso_joint.y=kinectNI.worldToProjective(kinectFeatures.getPosition(JOINT_TORSO)).y/kinectNI.getHeight();
    kinectOut.torso_joint.z=ofMap(kinectNI.worldToProjective(kinectFeatures.getPosition(JOINT_TORSO)).z, 1000, 3000, 0, 1);
    kinectOut.torso_joint.a=(kinectFeatures.getAcceleration(JOINT_TORSO).y+kinectFeatures.getAcceleration(JOINT_TORSO).x)/2;
    ofNotifyEvent(eventKinectInfo, kinectOut, this);
}

///--------------------------------------------------------------
void PMMotionExtractor::draw()
{
    kinectNI.drawImage();
//    cout<<kinectNI.worldToProjective(kinectFeatures.getPosition(JOINT_LEFT_HAND)).z << endl;
//    //prova
//    ofDrawEllipse(kinectNI.worldToProjective(kinectFeatures.getPosition(JOINT_LEFT_HAND)).x, kinectNI.worldToProjective(kinectFeatures.getPosition(JOINT_LEFT_HAND)).y, 20, 20);
//    ofDrawEllipse(kinectNI.worldToProjective(kinectFeatures.getPosition(JOINT_RIGHT_HAND)).x, kinectNI.worldToProjective(kinectFeatures.getPosition(JOINT_RIGHT_HAND)).y, 20, 20);
//    ofDrawEllipse(kinectNI.worldToProjective(kinectFeatures.getPosition(JOINT_HEAD)).x, kinectNI.worldToProjective(kinectFeatures.getPosition(JOINT_HEAD)).y, 20, 20);
//    ofDrawEllipse(kinectNI.worldToProjective(kinectFeatures.getPosition(JOINT_TORSO)).x, kinectNI.worldToProjective(kinectFeatures.getPosition(JOINT_TORSO)).y, 20, 20);
    //font.drawString(ofToString(kinectFeatures.getAcceleration(JOINT_RIGHT_HAND).y), kinectNI.worldToProjective(kinectFeatures.getPosition(JOINT_LEFT_HAND)).x, kinectNI.worldToProjective(kinectFeatures.getPosition(JOINT_LEFT_HAND)).y);
}

///--------------------------------------------------------------
void PMMotionExtractor::exit()
{
    kinectNI.stop();
}