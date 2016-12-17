#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    
    ofBackground(0,0,0);
    ofEnableAlphaBlending();
    ofSetLogLevel(OF_LOG_VERBOSE);
    ofSetLogLevel("ofXml", OF_LOG_SILENT);
    
    image.setup("img/", "img.cfg");
}

//--------------------------------------------------------------
void ofApp::update(){
}

//--------------------------------------------------------------
void ofApp::draw(){
    
    ofSetColor(255);
    ofEnableAlphaBlending();
    
    image.draw(0,0);
    
    ofSetColor(255);
    stringstream help;
    help << "[App]:\n";
    help << "keys [ ] - change image\n";
    help << "s - save state\n";
    ofDrawBitmapStringHighlight(help.str(), 10, ofGetHeight() - 100);
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    if (key == 's') image.saveState();
    if (key == ']') image.loadNext();
    if (key == '[') image.loadPrevious();
}

void ofApp::exit() {}
