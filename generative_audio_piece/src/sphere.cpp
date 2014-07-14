#include "sphere.h"

sphere::sphere() {
    
}

sphere::~sphere() {
    
    
}

//--------------------------------------------------------------
void sphere::setup(int posX, int posY, int posZ, int size) {
    
    sphereRadius = size;
    sphereRes = 3;
    spherePulse = 0;
    ofSetSphereResolution(sphereRes);
    sphereShell.set(sphereRadius, sphereRes);
    rotation = 0;
    counter = 0;
    alpha = 0;
    point.set(posX, posY, posZ);
    
    
    
}

//--------------------------------------------------------------
void sphere::update(){
    
    counter += 1;
    
    if (counter >= 20 && counter <= 200) {
        
        alpha += 2;
    }
    
    rotation += 0.33f;
    
    timeOfDay = ofGetHours();
    //cout << timeOfDay << endl;
    
    // Change color of Orbs depending on time of day user views the application 
    
    if (timeOfDay == ofWrap(timeOfDay, 1, 12)) {
        
        colorChange = colorChange.salmon;
        
    }
    if (timeOfDay == ofWrap(timeOfDay, 12, 18)) {
        
        colorChange = colorChange.lightYellow;
        
    }
    if (timeOfDay == ofWrap(timeOfDay, 18, 24)) {
        
        colorChange = colorChange.crimson;
    }
    
    
    
}

//--------------------------------------------------------------
void sphere::draw(){
    
    ofPushMatrix();
    ofTranslate(point.x, point.y, point.z);
    ofScale(1.0, 1.0);
    ofRotateX(rotation);
    ofRotateY(rotation);
    ofSetColor(ofColor::black, alpha);
    sphereShell.drawWireframe();
    ofSetColor(colorChange, 100);
    sphereShell.drawFaces();
    ofPopMatrix();
    
}



