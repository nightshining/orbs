#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup(){
    
    ///   SPHERES SETUP   ///
    
    ofSetVerticalSync(true);
    ofSetFullscreen(false);
    ofSetWindowTitle("M.Romeo");
    ofSetFrameRate(60);
    ofBackground(255);
    ofSetCircleResolution(60);
    
    int objectAmount = 100;
    
    sphere temp; //make temp class!
    
    for (int i = 0; i < objectAmount; i++) {
        
        redObjects.push_back(temp);   
    }
    
    for (int i = 0; i < redObjects.size(); i++) {
        
        position.set(ofRandom(ofGetWidth()), ofRandom(ofGetHeight()), ofRandom(-200, 200));
        
        redObjects[i].setup(position.x, position.y, position.z, ofRandom(5, 30));
        
        //individual noise
        noiseObjects.push_back(ofVec3f(ofRandom(0, 10000), ofRandom(0, 10000), ofRandom(0, 10000)));
    }
    
    ///   AUDIO SETUP   ///
    
    delay = ofxAudioUnit(kAudioUnitType_Effect,
                          kAudioUnitSubType_Delay);
        
    
    //Load a bunch of aif files using ofDirectory. This is very useful when using multiple sound files.
    
    string path = ofToDataPath("");
    
    ofDirectory dir(path);
    dir.allowExt("aif");
    
    //cout << dir.listDir() << endl; //total amount of files with .aif ext
    
    int fileAmount = dir.listDir();
    fileExt.resize(fileAmount);
    
    for (int i = 0; i < fileExt.size(); i++ ) {
        fileExt[i] = dir.getPath(i);
    }
    
    for (int i = 0; i < fileExt.size(); i++) {
        file.setFile(fileExt[i]);
    }
    
    constantAmbience.setFile(ofFilePath::getAbsolutePath("pads.aif"));
    
    mixer.setInputBusCount(2);
    
    file.connectTo(delay).connectTo(mixer, 0);
    constantAmbience.connectTo(mixer, 1);
    
    mixer.connectTo(output);
    
    introVolume = 0.0;
    mixer.setOutputVolume(introVolume);

    output.start();

    
    constantAmbience.play();
    constantAmbience.loop();
    
    randomSample = 0;
    counterObject = 0;
    
    ///   INTERACTION SETUP   ///
    
    moveHand.setup();
    
    font.loadFont("Junction-light.otf", 12);
    title.loadFont("Junction-bold.otf", 20);
    
}

//--------------------------------------------------------------
void testApp::update(){
   
    /// SPHERES UPDATE  ///
       
    for (int i = 0; i < redObjects.size(); i++) {
        
        //individual noise
        
        float time = ofGetElapsedTimef();
        float timeScale = 5.0;
        float displacementScale = 2.75;
        
        ofVec3f timeOffsets = noiseObjects[i];
        
        redObjects[i].point.x += (ofSignedNoise(time * timeScale + timeOffsets.x)) * displacementScale;
        redObjects[i].point.y += (ofSignedNoise(time * timeScale + timeOffsets.y)) * displacementScale;
        redObjects[i].point.z += (ofSignedNoise(time * timeScale + timeOffsets.y)) * displacementScale;
        
        redObjects[i].update();
               
    }
    
    redObjects[counterObject].colorChange.set(0, 255, 180, 90);
    
    if (counterObject == redObjects.size()) {
        
        counterObject = 0;
    }
    
    
    //cout << redObjects.size() << endl;
    
    ///     AUDIO UPDATE    ///
    introVolume += 0.01;
    
    mixer.setOutputVolume(introVolume);

    if (introVolume >= 0.90) {
        introVolume = 0.95;
    }
    
    //UNCOMMENT to automatically generate random tones
    
    /* generateRandomSample = ofRandom(100);
    
    if (generateRandomSample == 50) {
       triggerSample();
    } */
    
    ///     INTERACTION UPDATE     ///
    ///Trigger samples by movement
    
    moveHand.update();
    
    
     //Use the most left, middle, and right zones of screen
    if (moveHand.zone[0] >= 500) {
        
        triggerSample();
        reactiveCircle.set(0, 255, 180, 90);
        moveHand.zone[0] = 0;
        
        }
        else
        {
        reactiveCircle = redObjects[0].colorChange;
        }
    

}

//--------------------------------------------------------------
void testApp::draw(){

    cam.begin();
    for (int i = 0; i < redObjects.size(); i++) {
        
        redObjects[i].draw();
    }
    cam.end();
    
    
    //cout << "drag: " << cam.getDrag() << endl;
    //cout << "scale: " << cam.getScale() << endl;
    //cout << "pos: " << cam.getPosition() << endl;
    
    ofPoint menu1, menu2, menu3, menu4;
    menu1.set(ofGetWidth() - 250, 200);
    menu2.set(ofGetWidth() - 250, ofGetHeight() - 40);
    menu3.set(ofGetWidth() - 250, ofGetHeight() - 25);
    menu4.set(ofGetWidth() - 250, ofGetHeight() - 10);

    ofSetColor(ofColor::black, 150);
    
    title.drawString("ORBS", 50, 50);

    
    font.drawString("Wave hand near circle", menu1.x, menu1.y);
    font.drawString("Drag Mouse for rotation", menu2.x, menu2.y);
    font.drawString("Mouse + Control for zoom", menu3.x, menu3.y);
    font.drawString("Mouse + Alt for position", menu4.x, menu4.y);
    
    //UNCOMMENT to draw camera feed over application
    //moveHand.draw();
    
    
    ofPushMatrix();
    ofSetColor(reactiveCircle);
    ofFill();
    ofCircle(ofGetWidth() - 200, 100, 50);
    ofSetColor(150);
    ofNoFill();
    ofCircle(ofGetWidth() - 200, 100, 50);
    ofPopMatrix();
  
}

void testApp::triggerSample() {
    
    int randomSample = ofRandom(6);
    file.setFile(ofFilePath::getAbsolutePath(fileExt[randomSample]));
    file.play();
    counterObject++;
    
}

//--------------------------------------------------------------
void testApp::keyPressed(int key){

    if (key == ' ') {
        
        triggerSample();
    }
    
    if (key == 'd') {
        delay.showUI();
    }
   
    
}

//--------------------------------------------------------------
void testApp::keyReleased(int key){

}

//--------------------------------------------------------------
void testApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void testApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void testApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void testApp::dragEvent(ofDragInfo dragInfo){ 

}
