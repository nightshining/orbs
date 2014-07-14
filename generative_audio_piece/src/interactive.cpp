#include "interactive.h"

//--------------------------------------------------------------
void interactive::setup(){
    
    //Camera settings
    camWidth= 640;
    camHeight = 480;
    // testCapture.allocate(camWidth, camHeight, GL_RGB);
    //vidGrabber.setDeviceID(0); //sets
    vidGrabber.initGrabber(camWidth, camHeight);
    
    //CV motion settings
	cameraColorImage.allocate( camWidth, camHeight );
	cameraGrayImage.allocate( camWidth, camHeight );
	cameraGrayPrevImage.allocate( camWidth, camHeight );
	cameraGrayDiffImage.allocate( camWidth, camHeight );
	cameraDiffFloatImage.allocate( camWidth, camHeight );
	cameraMotionFloatImage.allocate( camWidth, camHeight );
    
    
    numZones = 5; //this sets up how many motion zones you're working with
    
    historySize = 3; //CHANGE this value to average over a smaller amount of values ie 2 would be averaging over 2 frames, 60 frames is more like 2 seconds of values
    
    //Init some vectors...
    zone.assign(numZones,0.0);
    smoothedZone.assign(numZones, 0.0);
    
    for (int i=0; i<numZones; i++){
        vector<float> temp;
        temp.assign(200,0.0);
        motionGraphs.push_back(temp);
        
        vector<int> smoothTemp;
        smoothTemp.assign(historySize,0.0);
        zoneHistory.push_back(smoothTemp);
    }
    
    trailsOn = true;
    
    trailBlur = 1; //amount of blur
    
    graphYScale = 500; //this sets your ceiling on how many pixels is your maximum value for motion
    
    cameraMotionFadeAmount = 0.0; //this sets the fade time for the white streaky pixels - 0 is no fade, .99 is heavy slow feedback
    
    
    
}

//--------------------------------------------------------------
void interactive::update(){
    
    bool bNewFrame = false;
    
    vidGrabber.update();
    bNewFrame = vidGrabber.isFrameNew();
    
    if( bNewFrame )
	{
		updateMotion( vidGrabber.getPixels() );
    }
    
    
}

void interactive::updateMotion(unsigned char *pixels){
    //--------------------------------------------------------------
    
    cameraColorImage.setFromPixels( pixels, camWidth, camHeight );
    
    cameraGrayPrevImage	= cameraGrayImage;
    cameraGrayImage		= cameraColorImage;
    
    cameraGrayDiffImage.absDiff( cameraGrayImage, cameraGrayPrevImage ); //take difference between current frame and previous frame
    cameraGrayDiffImage.threshold( 30 );
    
    if(trailsOn){ //draw motion trails - doesn't really effect motion valuez
        cameraDiffFloatImage	= cameraGrayDiffImage;
        cameraMotionFloatImage	*= cameraMotionFadeAmount;
        cameraMotionFloatImage	+= cameraDiffFloatImage;
        cameraMotionFloatImage.blurGaussian( trailBlur );
    }
    
    for (int i=0; i<numZones; i++){
        
        //zone[i] = cameraGrayDiffImage.countNonZeroInRegion(i*(camWidth/numZones), 0,(camWidth/numZones), camHeight); //for each zone - give me the number of white pixels detected in that window - pixels are turned white because of motion (from absolute differencing the 2 frames)
        //cout << zone[i] << endl;
        zone[i] = cameraGrayDiffImage.countNonZeroInRegion(50, 50, 50, 50);
        
        
        zoneHistory[i].push_back(zone[i]); //put the zone value into a history keeper
        
        int sum = 0;
        for (int j=0; j<zoneHistory[i].size(); j++) {
            sum = sum + zoneHistory[i][j]; //add up all the values in the history
        }
        
        smoothedZone[i] = sum/zoneHistory[i].size(); //take their average (divide the sum of all history values by the number of history values)
        
        if(zoneHistory[i].size()>=historySize){
            zoneHistory[i].erase(zoneHistory[i].begin(),zoneHistory[i].begin()+1);
        } //erase old history values
        
        float scaledVal = ofMap(smoothedZone[i], 0, graphYScale, 0.0, 1.0, true);         //scale the pixel count values between 0 and 1
        
        motionGraphs[i].push_back(scaledVal); //this is for the motion graphs
        if(motionGraphs[i].size()>=200){
            motionGraphs[i].erase(motionGraphs[i].begin(),motionGraphs[i].begin()+1);
        } //make sure the values don't get too high
        
    
    }
    
}

//--------------------------------------------------------------
void interactive::draw(){
    
    ofBackground(0); //clear the buffer!
    

    if(trailsOn){ //draw trails
        ofEnableBlendMode(OF_BLENDMODE_ADD);
        ofSetColor(255, 255, 255, 200);
        cameraMotionFloatImage.draw(0,0, camWidth, camHeight);
    }
    
    ofSetColor(255, 255, 255,255);
    vidGrabber.draw(0, 0, camWidth, camHeight); //Draw camera feed
    ofDisableBlendMode();
    
    //Draw motion graphs underneath sections
    for(int i=0; i<numZones; i++){
        
        if(i==0){
            ofSetColor(200, 0, 255);
        }
        if(i==1){
            ofSetColor(100, 200, 200);
        }
        if(i==2){
            ofSetColor(100, 200, 100);
        }
        if(i==3){
            ofSetColor(50, 200, 200);
        }
        if(i==3){
            ofSetColor(50, 50, 200);
        }
        
        ofPushMatrix();
        ofTranslate(i*(camWidth/numZones), 550);
        ofScale(0.5,0.2);
        ofBeginShape();
        for (int j = 0; j < motionGraphs[i].size(); j++){
            if( j == 0 ) ofVertex(j, 200);
            
            ofVertex(j, 200 - motionGraphs[i][j] * 200);
            
            if( j == motionGraphs[i].size() -1 ) ofVertex(j, 200);
        }
        ofEndShape(false);
        
        
        ofSetColor(255);
        ofPopMatrix();
        ofDrawBitmapString("Zone " + ofToString(i), i*(camWidth/numZones), camHeight+20);
        ofDrawBitmapString(ofToString(smoothedZone[i]), i*(camWidth/numZones), camHeight+42);
        
        
        ofLine(i*(camWidth/numZones), 0, i*(camWidth/numZones), camHeight);
        
    
    }
    
}
