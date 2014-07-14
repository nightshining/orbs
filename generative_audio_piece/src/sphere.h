#pragma once

#include "ofMain.h"

class sphere : public ofBaseApp{
    
public:
    sphere(); //constructor
    ~sphere(); //deconstructor
    void setup(int posX, int posY, int posZ, int size);
    void update();
    void draw();
    
    ofSpherePrimitive sphereShell;
    int sphereRadius, sphereRes, spherePulse, counter, alpha, timeOfDay;
    float rotation;
    ofColor colorChange;
    ofVec3f point;
    
    
    
};
