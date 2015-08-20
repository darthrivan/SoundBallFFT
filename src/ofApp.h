#pragma once

#include "ofMain.h"
#include "ParticleSystem.h"
#include "ofxFFTBase.h"


#define BUFFER_SIZE 256

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
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);
    
        //*********************************
        //AUDIO
        //*********************************
        
        ofSoundStream soundStream;
        vector<float> samplesChannelL, samplesChannelR;
    
        ofxFFTBase fftChannelL, fftChannelR;
    
        void audioIn(float* input, int bufferSize, int nChannels);
        //*********************************
        //END OF AUDIO
        //*********************************
        
        
        //*********************************
        //SOUND BALL
        //*********************************
        
        ParticleSystem sys;
        
        //*********************************
        //END OF SOUND BALL
        //*********************************
		
};
