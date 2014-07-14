#pragma once

#include "ofMain.h"
#include "ofxOpenCv.h"


class interactive : public ofBaseApp{
    
public:
    void setup();
    void update();
    void draw();
    
    void updateMotion(unsigned char *pixels);
    
    
    ofVideoGrabber  vidGrabber;
    int camWidth, camHeight;
    
    ofxCvColorImage			cameraColorImage;
    ofxCvGrayscaleImage		cameraGrayImage;
    ofxCvGrayscaleImage		cameraGrayPrevImage;
    ofxCvGrayscaleImage		cameraGrayDiffImage;
    ofxCvFloatImage			cameraDiffFloatImage;
    ofxCvFloatImage			cameraMotionFloatImage;
    float cameraMotionFadeAmount;
    int trailBlur;
    
    vector <int> zone;
    
    int historySize;
    
    vector < vector <int> > zoneHistory;
    
    vector <int> smoothedZone;
    
    int numZones;
    
    int graphYScale;
    
    int motionThresh;
    
    vector < vector <float> > motionGraphs;
    
    bool trailsOn;
    
    
    
};