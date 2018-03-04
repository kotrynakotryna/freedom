#include "ofApp.h"

/*
 
 fill mask buffer with silhouette (black pixels)
 
 loop through pixels mask buffer
 if mask pixel is black
 display relative video pixel
 else
 don't display relative video pixel
 
 */


//--------------------------------------------------------------
void ofApp::setup(){
    
    // set pixel format to include alpha so that we can manipulate pixel opacity
    vidPlayer.setPixelFormat(OF_PIXELS_RGBA);
    vidPlayer.load("j.mp4");
    vidPlayer.play();
    
    trump.setPixelFormat(OF_PIXELS_RGBA);
    trump.load("tr.mp4");
    trump.play();
    
    bLearnBackground = false;
    
    vidGrabber.setVerbose(true);
    vidGrabber.initGrabber(1280,720);
    
    grayBg.allocate(1280,720);
    grayDiff.allocate(1280,720);
    
    // these variables are used to allocate memory for the pixels, textures and buffers
    // i guess you will need to make the video dimensions the same as the screen (or projection) dimensions
    width = vidPlayer.getWidth();
    height = vidPlayer.getHeight();
    
    
    // allocate memory for pixels, textures and buffers
    maskPixels.allocate(width, height, OF_PIXELS_RGBA);
    vidPixels.allocate(width, height, OF_PIXELS_RGBA);
    
    
    vidTex.allocate(width, height, GL_RGBA);
    
    
    maskBuffer.allocate(width, height, GL_RGBA);
    vidBuffer.allocate(width, height, GL_RGBA);
    
}

//--------------------------------------------------------------
void ofApp::update() {
    
    vidGrabber.update();
    //do we have a new frame?
    if (vidGrabber.isFrameNew()){
        colorImg.setFromPixels(vidGrabber.getPixels());
        grayImage = colorImg; // convert our color image to a grayscale image
        if (bLearnBackground == true) {
            grayBg = grayImage; // update the background image
            bLearnBackground = false;
        }
        grayDiff.absDiff(grayBg, grayImage);
        grayDiff.threshold(80);
        contourFinder.findContours(grayDiff, 5, (340*240)/4, 4, false, true);
    }
    
    
    if(vidPlayer.isFrameNew()) {
        // store video pixels in 'vidPixels' object
        vidPixels = vidPlayer.getPixels();
        
        // store mask buffer in 'maskPixels' object
        maskBuffer.readToPixels(maskPixels, 0);
        
        // loop through all pixels in mask
        for(int i = 0; i < maskPixels.size(); i+=4) {
            // temporarily store the relative video pixel colour
            ofColor vidMaskCol = vidPixels.getColor(i);
            // if mask pixel is black (is part of the silhouette)
            if(maskPixels.getColor(i) == ofColor::black) {
                // set temp colour to full opacity
                vidMaskCol.a = 255;
            } else {
                // set temp colour to transparent
                vidMaskCol.a = 0;
            }
            // set relative pixel colour with temp colour
            vidPixels.setColor(i, vidMaskCol);
        }
        // stick video pixel data (with updated mask) into video texture
        vidTex.loadData(vidPixels);
    }
    
    vidPlayer.update();
    trump.update();

    
}

//--------------------------------------------------------------
void ofApp::draw(){
    
    maskBuffer.begin();
    //ofBackground(255);
    
    // THIS IS WHERE YOU DISPLAY THE OPENCV SILHOUETTE
    ofSetHexColor(0xffffff);
    grayDiff.draw(0, 0, width, height);
    // ofColor c(255, 255, 255, 150);
    //        ofFill();
    //        ofSetColor(0);
    //        ofDrawCircle(mouseX, mouseY, 50);
    maskBuffer.end();
    
    vidBuffer.begin();
    ofBackground(255,0,0);
    trump.draw(0, 0, width, height);
    
    // THIS IS WHERE YOU DISPLAY THE VIDEO TEXTURE (AFTER IT HAS BEEN MANIPULATED)
    ofSetColor(255);
    vidTex.draw(0, 0, width, height);
    vidBuffer.end();
    
    
    
    // no need to draw the mask
    // maskBuffer.draw(0, 0, width, height);
    //grayDiff2.draw(0, 0, width2, height2);
    
    vidBuffer.draw(0, 0, width, height);
    
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){
    
}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){
    
}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){
    
}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){
    
}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){
    
}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){
    
}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){
    
}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){
    
}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){
    
}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){
    
}

