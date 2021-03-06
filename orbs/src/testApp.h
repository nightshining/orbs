#pragma once

#include "ofMain.h"
#include "ofxAudioUnit.h"
#include "sphere.h"


class testApp : public ofBaseApp{

	public:
		void setup();
        void triggerSound();
		void update();
		void draw();

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

    //Audio
    
    ofxAudioUnitFilePlayer file, constantAmbience;
    ofxAudioUnitMixer mixer;
    ofxAudioUnit delay;
    vector<string> fileExt;
    int counterObject, randomSample;
    ofxAudioUnitOutput output;
    float introVolume;
    int generateRandomSample;
    
};
