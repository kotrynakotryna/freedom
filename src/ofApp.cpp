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
    //loading the audio file that will be playing as a background of the piece
    back.load("background.wav");
    //making the sound loop
    back.setLoop(true);
    //playing the sound
    back.play();

    //synchronizes the redraw of the screen to the vertical refresh of the screen at 60 frames per second
    ofSetVerticalSync(true);
    //setting the display resolution
    ofSetWindowShape(1920,1080);

    //the framebuffer that will have an OpenCV sillhouette
    myFbo.allocate(1920,1080);
    
    
    //set pixel format to include alpha so that we can manipulate pixel opacity
    vidPlayer.setPixelFormat(OF_PIXELS_RGBA);
    //loading the backdgrounf video file
    vidPlayer.load("negativee.mp4");
    //playin the background video
    vidPlayer.play();
    
    //set pixel format to include alpha so that we can manipulate pixel opacity
    trump.setPixelFormat(OF_PIXELS_RGBA);
    //loading another video that will be in the sillhouette
    trump.load("good.mp4");
    //playing the video
    trump.play();
    
    //vidGrabber is the ofVideoGrabber class that grabs the component
    //to provide the access to the live cameras
    vidGrabber.setVerbose(true);
    //listin devices in the console to see what devices are detected by the computers
    //to find the one the one that needs to be used
    vidGrabber.listDevices();
    //in this case the camera's ID that is plugged to the computer is 1
    vidGrabber.setDeviceID(1);
    //setting the resolution of the camera that will be displaying the view
    vidGrabber.initGrabber(1920,1080);
    
    //background image(video)
    grayBg.allocate(1920,1080);
    //difference image(video) between background and source
    grayDiff.allocate(1920,1080);
    
    //these variables are used to allocate memory for the pixels, textures and buffers
    width = vidPlayer.getWidth();
    height = vidPlayer.getHeight();
    
    
    //allocates memory for mask and video pixels, textures and buffers
    maskPixels.allocate(width, height, OF_PIXELS_RGBA);
    vidPixels.allocate(width, height, OF_PIXELS_RGBA);
    
    
    vidTex.allocate(width, height, GL_RGBA);
    myFbo.allocate(width, height, GL_RGBA);
    vidBuffer.allocate(width, height, GL_RGBA);
    
}

//--------------------------------------------------------------
void ofApp::update() {
    
    //updates the live camera
    vidGrabber.update();
    
    //the following code is to create the threshold with OpenCV of the
    //video provided by the live camera
    //the threshold will allow me to detect the person standing in front of the camera
    //and will create the sillhouette if for example the person is brighter than what's
    //in the background
    //the threshold will make the sillhouette and what's brighter appear black, and what's further appear white
    
    //the if statement checking whether we there is a new frame
    if (vidGrabber.isFrameNew()){
        colorImg.setFromPixels(vidGrabber.getPixels());
        grayImage = colorImg; //converts the color video to a grayscale image
        if (bLearnBackground == true) {
            grayBg = grayImage; // update the background image
            bLearnBackground = false;
        }
        grayDiff.absDiff(grayBg, grayImage); //calculates the per-element absolute difference between two arrays or between an array and a scalar
        grayDiff.threshold(150); //the intensity of the threshold, the bigger the number the more detailed sillhouette will be
        contourFinder.findContours(grayDiff, 5, (340*240)/4, 4, false, true); //the contour finder allows you to detect objects in a scene by looking at contrast between adjoining pixels
    }
    
    //the following code is to make the the mask pixels transparent
    //therefore the pixels that are black will become transparent, this way
    //I will be able to play the video in the sillhouette
    if(vidPlayer.isFrameNew()) {
        //storing video pixels in 'vidPixels' object
        vidPixels = vidPlayer.getPixels();
        
        //storing mask buffer in 'maskPixels' object
        myFbo.readToPixels(maskPixels, 0);
        
        //looping through all pixels in mask
        for(int i = 0; i < maskPixels.size(); i+=4) {
            //temporarily storing the relative video pixel colour
            ofColor vidMaskCol = vidPixels.getColor(i);
            //if mask pixel is black (is part of the silhouette)
            if(maskPixels.getColor(i) == ofColor::black) {
                //set temp colour to full opacity
                vidMaskCol.a = 255;
                
            } else {
                //set temp colour to transparent
                vidMaskCol.a = 0;
            }
            // set relative pixel colour with temporary colour
            vidPixels.setColor(i, vidMaskCol);
        }
        //loading video pixel data (with updated mask) into video texture
        vidTex.loadData(vidPixels);
        
    }
    
    //updates both video video player objects
    vidPlayer.update();
    trump.update();
 
    
}

//--------------------------------------------------------------
void ofApp::draw(){

    //placing the openCV sillhouette into the myFbo framebuffer
    myFbo.begin();
    //displaying the openCV sillhouette that is set with the specific resolution
    grayDiff.draw(0, 0, 1920,1080);
    //finishing drawing the myFbo frame buffer
    myFbo.end();
    
    //placing the video after it has been manipulated inside the mask
    vidBuffer.begin();
    //displaying one of the videos after its been manipulated, with the specific resolution
    trump.draw(0, 0, 1920,1080);
    
    //displaying the video pixel data after its been manipulated
    vidTex.draw(0, 0, width,height);
    //finishing drawing the vidBuffer frame buffer
    vidBuffer.end();
    
    //begins to draw the myFbo frame buffer where the threshold silhouette will be displayed
    myFbo.draw(0, 0, 1920,1080);
    //begins to draw the vidBuffer frame buffer that will play the video in the sillhouette, or what was
    //black pixels in the threshold
    vidBuffer.draw(0, 0,1920,1080);
    
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


