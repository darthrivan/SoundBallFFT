#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    //*********************************
    //AUDIO
    //*********************************
    
    // 0 output channels,
	// 2 input channels
	// 44100 samples per second
	// 256 samples per buffer
	// 4 num buffers (latency)
	
	//soundStream.listDevices();
	
    //if you want to set a different device id
	soundStream.setDeviceID(0); //bear in mind the device id corresponds to all audio
    //devices, including  input-only and output-only devices.
    
    ofSoundStreamSetup(0,2,this, 44100,BUFFER_SIZE, 4);
    
    samplesChannelL.assign(BUFFER_SIZE, 0.0);
    samplesChannelR.assign(BUFFER_SIZE, 0.0);
    
    //*********************************
    //END OF AUDIO
    //*********************************
    
    
    //*********************************
    //SOUND BALL
    //*********************************
    
    ofSetVerticalSync(true);
    ofSetFrameRate(50);
    ofEnableAlphaBlending();
    ofBackground(0,0,0);
    
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glEnable(GL_COLOR_MATERIAL);
    glEnable(GL_DEPTH_TEST);
    
    sys.init();
    
    //*********************************
    //END OF SOUND BALL
    //*********************************
}

//--------------------------------------------------------------
void ofApp::update(){
    //*********************************
    //AUDIO
    //*********************************
    
    // update the sound FFT:
    fftChannelL.update();
    fftChannelR.update();
    
    vector<float> sampL = fftChannelL.getFftNormData();
    int sampSizeL = sampL.size();
    
    for (int i = 0; i < sampSizeL; ++i) {
        cout << sampL[i] << endl;
    }
    
    //*********************************
    //END OF AUDIO
    //*********************************
    
    
    //*********************************
    //SOUND BALL
    //*********************************
    
    sys.modRad(1); //Modify particle system's radius
    sys.modPartRad(1); //Modify some particles size depending on the HIGHs
    
    //*********************************
    //END OF SOUND BALL
    //*********************************
}

//--------------------------------------------------------------
void ofApp::draw(){
    ofBackgroundGradient(ofColor(0), ofColor(0, 180, 200));
    
    //*********************************
    //AUDIO
    //*********************************
    
    
    //*********************************
    //END OF AUDIO
    //*********************************
    
    
    //*********************************
    //SOUND BALL
    //*********************************
    
    ofTranslate(ofGetWidth()/2, ofGetHeight()/2, 0);
    sys.draw();
    
    //*********************************
    //END OF SOUND BALL
    //*********************************
}

//--------------------------------------------------------------
void ofApp::audioIn(float* input, int bufferSize, int nChannels){
    for (int i = 0; i < BUFFER_SIZE; ++i) {
        samplesChannelL[i] = input[i * 2 + 0];
        samplesChannelR[i] = input[i * 2 + 1];
    }
    
    float* dataL = &samplesChannelL[0];
    float* dataR = &samplesChannelR[0];
    
    fftChannelL.audioIn(dataL);
    fftChannelR.audioIn(dataR);
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
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}
