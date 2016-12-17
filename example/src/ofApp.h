#pragma once

#include "ofMain.h"
#include "ofxFolderImage.h"

class ofApp : public ofBaseApp{
    
public:
    
    void setup();
    void update();
    void draw();
    void exit();
    void keyPressed(int key);
    
    ofxFolderImage image;
};
