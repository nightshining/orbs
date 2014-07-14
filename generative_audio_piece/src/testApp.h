#pragma once

#include "ofMain.h"
#include "ofxAudioUnit.h"
#include "sphere.h"
#include "interactive.h"


class testApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();
        void triggerSample();
        //function for triggering random samples and updating color of objects as sound changes.
    
		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);
    
    //Spheres
    
    vector <sphere> redObjects;
    ofEasyCam cam;
    ofVec3f position;
    vector <ofVec3f> noiseObjects;
    ofColor reactiveCircle;

    //Audio
    
    ofxAudioUnitFilePlayer file, constantAmbience;
    ofxAudioUnitMixer mixer;
    ofxAudioUnit delay;
    vector<string> fileExt;
    int counterObject, randomSample;
    ofxAudioUnitOutput output;
    float introVolume;
    int generateRandomSample;
    
    ///Interaction
    
    interactive moveHand;
    
    ///Font
    ofTrueTypeFont font, title;
    
    
    /* NOTE:
     
     These examples are more about what is happening with audio in the 
     testApp.cpp. Here, my focus is thinking about constructive ways to utilize
     sound samples being triggered randomly or through user interaction. 
     
     */
    
};
