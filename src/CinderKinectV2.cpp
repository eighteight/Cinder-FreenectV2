//
//  ofxKinectV2.cpp
//  kinectExample
//
//  Created by Theodore Watson on 6/23/14.
//
//

#include "CinderKinectV2.h"

//--------------------------------------------------------------------------------
CinderKinectV2::CinderKinectV2(){
    bNewFrame  = false;
    bNewBuffer = false;
    bOpened    = false;
    lastFrameNo = -1;
    
    //set default distance range to 50cm - 600cm
    minDistance.set("minDistance", 500, 0, 12000);
    maxDistance.set("maxDistance", 6000, 0, 12000);
}

//--------------------------------------------------------------------------------
CinderKinectV2::~CinderKinectV2(){
    close();
}

//--------------------------------------------------------------------------------
bool CinderKinectV2::open(){
    close(); 
    
    bNewFrame  = false;
    bNewBuffer = false;
    bOpened    = false;
    
    int retVal = protonect.openKinect(ofToDataPath(""));
    if(retVal==0){
        lastFrameNo = -1;
        startThread();
    }else{
        return false;
    }
    
    bOpened = true;
    return true;
}

//--------------------------------------------------------------------------------
void CinderKinectV2::threadedFunction(){
    while(isThreadRunning()){
        protonect.updateKinect(rgbPixelsBack, depthPixelsBack);
        rgbPixelsFront.swap(rgbPixelsBack);
        depthPixelsFront.swap(depthPixelsBack);
        
        lock();
        bNewBuffer = true;
        unlock();
        
        ofSleepMillis(2);
    }
}

//--------------------------------------------------------------------------------
void CinderKinectV2::update(){
    if( ofGetFrameNum() != lastFrameNo ){
        bNewFrame = false;
        lastFrameNo = ofGetFrameNum();
    }
    if( bNewBuffer ){
        lock();
            rgbPix = rgbPixelsFront;
            rawDepthPixels = depthPixelsFront;
            bNewBuffer = false;
        unlock();
        
        if( rawDepthPixels.size() > 0 ){
            if( depthPix.getWidth() != rawDepthPixels.getWidth() ){
                depthPix.allocate(rawDepthPixels.getWidth(), rawDepthPixels.getHeight(), 1);
            }
        
            float * pixelsF         = rawDepthPixels.getPixels();
            unsigned char * pixels  = depthPix.getPixels();
                
            for(int i = 0; i < depthPix.size(); i++){
                pixels[i] = ofMap(rawDepthPixels[i], minDistance, maxDistance, 255, 0, true);
                if( pixels[i] == 255 ){
                    pixels[i] = 0;
                }
            }

        }
        
        
        bNewFrame = true; 
    }
}

//--------------------------------------------------------------------------------
bool CinderKinectV2::isFrameNew(){
    return bNewFrame; 
}

//--------------------------------------------------------------------------------
ofPixels CinderKinectV2::getDepthPixels(){
    return depthPix;
}

//--------------------------------------------------------------------------------
ofPixels CinderKinectV2::getRgbPixels(){
    return rgbPix; 
}

//--------------------------------------------------------------------------------
void CinderKinectV2::close(){
    if( bOpened ){
        waitForThread(true);
        protonect.closeKinect();
        bOpened = false;
    }
}


