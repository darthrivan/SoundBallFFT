//
//  ParticleSystem.h
//  SoundBallFFT
//
//  Created by blag on 11/08/15.
//
//

#ifndef __SoundBallFFT__ParticleSystem__
#define __SoundBallFFT__ParticleSystem__

#include <iostream>
//#include <GLUT/glut.h>

#include "Particle.h"

#define NUM_PARTICLES 3000
#define MAX_CONNECTIONS 10
#define DISTANCE_CONNECTIONS 20
#define RADIUS 200

class ParticleSystem : public ofBaseApp {
public:
    
    ParticleSystem();
    void update();
    void draw();
    void init();
    void modRad(float modifier);
    void modPartRad(float highDetect);
    
private:
    Particle particles[NUM_PARTICLES]; //Original particles
    float connectionsModifier = 1.0; //Variable that changes the connections distance to adjust
                                     //with the radius movement using sound
    int nDrawnParticles;
    
    void connectWithClosest(int ori_id, float orix, float oriy, float oriz);
};

#endif /* defined(__SoundBallFFT__ParticleSystem__) */
