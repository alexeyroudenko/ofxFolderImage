#pragma once

#include "ofMain.h"

class ofxFolderImage {
    
public:
    ofEvent<string> onPhotoLoad;
    
    int current;
    string loadedFileName = "";
    ofImage image;
    
    //--------------------------------------------------------------
    void setup(string folder_, string name_ = ""){
        ofSetLogLevel("ofDirectory", OF_LOG_SILENT);
        name = name_;
        folder = folder_;
        current = 0;
        if (name_ != "") {
            loadState();
            loadAt(current);
        }
    }
    
    void loadByFilemame(string fileName) {
        ofLogVerbose("ofxFolderImage", "loadByFilemame: " + fileName);
        image.load(dir.getAbsolutePath() + "/" + fileName);
        ofNotifyEvent(onPhotoLoad, fileName);
        loadedFileName = fileName;
        // TODO: set index
    }
    
    void loadAt(int number) {
        if (number == -1) loadState();
        string directory = folder;
        dir.listDir(directory);
        dir.sort();
        current = number;
        if (dir.size() <= current) current = 0;
        if (dir.size() != 0) {
            string fileName = dir.getPath(current);
            ofFile file(fileName);
            ofLogVerbose("ofxFolderImage", "load at "  + ofToString(current) + " " + file.getAbsolutePath());
            image.load(fileName);
            loadedFileName = fileName;
            ofNotifyEvent(onPhotoLoad, fileName);
        } else {
            ofLogVerbose("ofxFolderImage", "create empty for: " + dir.getAbsolutePath());
            loadedFileName = "";
            image = ofImage();
            ofNotifyEvent(onPhotoLoad, loadedFileName);
        }
    }
    
    int getCurrent() {
        return current;
    }
    
    void loadNext() {
        string directory = folder;
        dir.listDir(directory);
        dir.sort();
        
        current++;
        if (dir.size() <= current) current = 0;
        
        string fileName = dir.getPath(current);
        ofFile file(fileName);
        ofLogVerbose("ofxFolderImage", "load at "  + ofToString(current) + " " + file.getAbsolutePath());
        image.load(fileName);
        loadedFileName = fileName;
        ofNotifyEvent(onPhotoLoad, fileName);
    }
    
    void loadPrevious() {
        string directory = folder;
        dir.listDir(directory);
        dir.sort();
        
        current--;
        if (current < 0) current = dir.size() - 1;

        string fileName = dir.getPath(current);
        ofFile file(fileName);
        ofLogVerbose("ofxFolderImage", "load at "  + ofToString(current) + " " + file.getAbsolutePath());
        image.load(fileName);
        loadedFileName = fileName;
        ofNotifyEvent(onPhotoLoad, fileName);
    }
    
    string getFileName() {
        string directory = folder;
        dir.listDir(directory);
        dir.sort();
        return dir.getPath(current);
    }
    
    void loadState() {
        ofBuffer buffer = ofBufferFromFile("settings/" + name);
        current = ofToInt(buffer.getText());
        ofLogVerbose("ofxFolderImage", "loadState "  + ofToString(current) + " folder:" + folder + " name:" + name);
    }
    
    void saveState() {
        ofLogVerbose("ofxFolderImage", "saveState:" + ofToString(current) + " fileName:" + getFileName() +  " folder:" + folder + " name:" + name);
        ofFile file(ofToDataPath("settings/" + name), ofFile::WriteOnly);
        file << ofToString(current);
        file.close();
    }
    
private:
    string folder = "";
    string name = "";
    ofDirectory dir;
    
};
