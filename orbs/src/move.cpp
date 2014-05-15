#include "move.h"

//--------------------------------------------------------------
void move::setup(){
    
    width = ofGetWidth() / 4;
    height = ofGetHeight() / 4;
    
    vidGrabber.setVerbose(true);
    vidGrabber.initGrabber(width,height);
    vidGrabber.setDesiredFrameRate(25);
    
    colorImg.allocate(width,height);
	grayImage.allocate(width,height);
	grayBg.allocate(width,height);
	grayDiff.allocate(width,height);
    
	bLearnBakground = true;
	threshold = 100;
    
    cvPos.set(50, 50);
    
    getCentroid.set(0, 0, 0);
}

//--------------------------------------------------------------
void move::update(){
    
    
    bool bNewFrame = false;
    
    vidGrabber.update();
    bNewFrame = vidGrabber.isFrameNew();
    
    
	if (bNewFrame){
        
        colorImg.setFromPixels(vidGrabber.getPixels(), width,height);
        
        grayImage = colorImg;
		if (bLearnBakground == true){
			grayBg = grayImage;		// the = sign copys the pixels from grayImage into grayBg (operator overloading)
			bLearnBakground = false;
		}
        
		// take the abs value of the difference between background and incoming and then threshold:
		grayDiff.absDiff(grayBg, grayImage);
		grayDiff.threshold(threshold);
        
		// find contours which are between the size of 20 pixels and 1/3 the w*h pixels.
		// also, find holes is set to true so we will get interior contours as well....
		contourFinder.findContours(grayDiff, 20, (width * height)/ 3, 10, false);	// find holes
	}
    
}

//--------------------------------------------------------------
void move::draw(){
    
	// draw the incoming, the grayscale, the bg and the thresholded difference
	ofSetHexColor(0xffffff);
    //colorImg.draw(20,20);
	//grayImage.draw(360,20);
	//grayBg.draw(20,280);
    //grayDiff.draw(360,280);
    
	// then draw the contours:
    ofNoFill();
	ofSetColor(255);
    ofRect(cvPos.x, cvPos.y, width, height);
	ofFill();
	ofSetColor(100, 100, 100, 90);
    ofRect(cvPos.x, cvPos.y, width, height);
	
    //ofSetHexColor(0xffffff);
    ofSetColor(255, 0, 0);
	// or, instead we can draw each blob individually from the blobs vector
	// this is how to get access to them:
    for (int i = 0; i < contourFinder.nBlobs; i++){
        contourFinder.blobs[i].draw(cvPos.x, cvPos.y);
        
        contourFinder.blobs.at(0).centroid;
        
        //tap this variable for centroid data
        getCentroid = contourFinder.blobs.at(0).centroid;
        
		// draw over the centroid if the blob is a hole
		ofSetColor(255);
		if(contourFinder.blobs[i].hole){
            ofDrawBitmapString("hole", contourFinder.blobs[i].boundingRect.getCenter().x + cvPos.x,contourFinder.blobs[i].boundingRect.getCenter().y + cvPos.y);
            
            ofSetColor(255);
            
            
        }
    }
    
    // finally, a report:
	ofSetColor(255);
    ofDrawBitmapString("Click and Drag", cvPos.x + 40, cvPos.y + 10);
    
    ofDrawBitmapString("'Spacebar' REFRESH", cvPos.x + 25, cvPos.y + 150);
    
    
}

//--------------------------------------------------------------
void move::keyPressed(int key){
    
	if (key == ' '){
        
        bLearnBakground = true;
		
	}
    
    
}


