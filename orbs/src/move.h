#pragma once

#include "ofMain.h"
#include "ofxOpenCv.h"
#include "ofxCv.h"

class move : public ofBaseApp{
    
public:
    void setup();
    void update();
    void draw();
    void keyPressed(int key);
    
    ofVideoGrabber 		vidGrabber;
    
    
    ofxCvColorImage			colorImg;
    
    ofxCvGrayscaleImage 	grayImage;
    ofxCvGrayscaleImage 	grayBg;
    ofxCvGrayscaleImage 	grayDiff;
    
    ofxCvContourFinder 	contourFinder;
    
    int 				threshold;
    bool				bLearnBakground;
    
    ofPoint cvPos;
    ofVec3f getCentroid;
    
    int width, height;
    
};

