#pragma once

#include "ofMain.h"
#include "ofxOpenCv.h"


class ofApp : public ofBaseApp{
    
public:
    void setup();
    void update();
    void draw();
    
    void keyPressed(int key);
    void keyReleased(int key);
    void mouseMoved(int x, int y );
    void mouseDragged(int x, int y, int button);
    void mousePressed(int x, int y, int button);
    void mouseReleased(int x, int y, int button);
    void mouseEntered(int x, int y);
    void mouseExited(int x, int y);
    void windowResized(int w, int h);
    void dragEvent(ofDragInfo dragInfo);
    void gotMessage(ofMessage msg);
    
    //ofVideoPlayer class loads in movie files that allows to control
    //and play videos and to access the pixels of a given frame
    //this time I will be using two videos, one for the background
    //and another that will be inside openCv sillhouette
    ofVideoPlayer vidPlayer;
    ofVideoPlayer trump;
    
    //declaring the width and height variables
    //there will be vidPlayer size stored into the variables
    int width;
    int height;
    
    //declaring ofPixel objects to allow me to work with the blocks of pixels to manipulate videos
    ofPixels maskPixels;
    ofPixels vidPixels;
    
    //declaring the ofTexture class that will allow me to manipulate the texture of the video
    ofTexture vidTex;
    
    //using two frame buffers that are useful to help me to manipulate videos that are
    //in the frame buffer. As I will be using two videos that will play on top of each other
    //frame buffers allows me to use them as layers
    ofFbo maskBuffer;
    ofFbo vidBuffer;
    ofFbo myFbo;
    
    //boolean to check wether the backgdround is certain color
    bool bLearnBackground;
    //ofxVideoGrabber variable for the live camera
    ofVideoGrabber vidGrabber;
    
    //openCV addon variables used for the threshold
    ofxCvColorImage colorImg;
    ofxCvGrayscaleImage grayImage, grayBg, grayDiff;
    ofxCvContourFinder contourFinder;

    //declaring the variable that will used for the audio
    ofSoundPlayer   back;
};


