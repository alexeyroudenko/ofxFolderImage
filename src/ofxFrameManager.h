#pragma once

#include "ofMain.h"
#include "ofxFolderImage.h"

class ofxFrameManager {
    
public:
    ofxFolderImage bottom;
    ofParameter<bool>   active;
    
    void setup(string topPath_ = "images/top/",string bottomPath_ = "images/bottom/") {
        topPath = topPath_;
        bottomPath = bottomPath_;
        
        ofAddListener(bottom.onPhotoLoad, this, &ofxFrameManager::onFrameChange);
        bottom.setup(bottomPath, "settings/bottom_frame.cfg");
    }
    
    void saveState() {
        bottom.saveState();
    }

    void draw(int x, int y, int width, int height) {
        bottom.draw(x, y, width, height);
    }
    
    void drawTop(int x, int y, int width, int height) {
        if (hasTop) topImage.draw(x, y, width, height);
    }
    
    int getWidth() {return bottom.getWidth();}
    int getHeight() {return bottom.getHeight();}
    ofRectangle getFrame() { return ofRectangle(0, 0, getWidth(), getHeight());};

private:
    string topPath;
    string bottomPath;
    bool hasTop;
    
    ofImage topImage;
    
    void onFrameChange(string &fileName) {
        ofLogVerbose("ofFrameManager", "onFrameChange: " + fileName);
        ofFile file(fileName);
        
        ofFile topFile(topPath + file.getBaseName() + ".png");
        if (topFile.exists() == true) {
            ofLogVerbose("ofFrameManager", "load: " + topFile.getAbsolutePath());
            topImage.load(topFile.getAbsolutePath());
            hasTop = true;
        } else {
            ofLogVerbose("ofFrameManager", "skip (no top frame): " + topFile.getAbsolutePath());
            hasTop = false;
        }
        
    }
};
