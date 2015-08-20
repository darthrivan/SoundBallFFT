//
//  ParticleSystem.cpp
//  SoundBallFFT
//
//  Created by blag on 11/08/15.
//
//

#include "ParticleSystem.h"

ParticleSystem::ParticleSystem() {
    for(int i = 0; i < NUM_PARTICLES; i++) {
        float theta = ofRandom(0,TWO_PI);
        float u = ofRandom(-1,1);
        particles[i] = Particle(theta, u, RADIUS);
    }
    nDrawnParticles = 0; //We start by drawing no particles
}

void ParticleSystem::update() {
    for(int i = 0; i < NUM_PARTICLES; i++) {
        particles[i].update(RADIUS);
    }
}

void ParticleSystem::draw() {
    //ofSetColor(80,80,80);
    //glutSolidSphere(140, 64, 64);
    
    ofSetColor(255, 255, 255); //white
    for(int i = 0; i < nDrawnParticles; i++) { //Until nDrawnParticles and not until NUM_PARTICLES
        particles[i].draw();
    }
    if (nDrawnParticles < NUM_PARTICLES) ++nDrawnParticles;
}

void ParticleSystem::init() {
    for(int i = 0; i < NUM_PARTICLES; i++) { //We do initialize nDrawnParticles and not NUM_PARTICLES
        particles[i].update(RADIUS);
        connectWithClosest(i, particles[i].getPositionX(),
                           particles[i].getPositionY(),
                           particles[i].getPositionZ());
    }
}

void ParticleSystem::modRad(float modifier){
    // IF WE WANT THEM TO MOVE AS A WHOLE WE UNCOMMENT THIS
    //    connectionsModifier = modifier;
    //    for(int i = 0; i < NUM_PARTICLES; i++) {
    //        particles[i].updateRadius(RADIUS, modifier);
    //    }
    // AND COMMENT THIS. LEAVE THIS UNCOMMENTED AND ABOVE COMMENTED
    // TO CHANGE THE BEHAVIOUR TO SOME RANDOM PARTICLES AND NOT ALL
    connectionsModifier = modifier;
    for(int i = 0; i < NUM_PARTICLES; i++) {
        if (ofRandom(1) >= 0.5) particles[i].updateRadius(RADIUS, modifier);
    }
}

void ParticleSystem::modPartRad(float highDetect){
    for(int i = 0; i < nDrawnParticles; i++) {
        if (ofRandom(0, 1) > 0.5) {
            particles[i].setPartSizeModi(highDetect);
        }
    }
}

void ParticleSystem::connectWithClosest(int ori_id, float orix, float oriy, float oriz){
    int counter = particles[ori_id].getNumberNearParticles(); //To add just as many as the particle can
    int j = 0;
    while (counter < MAX_CONNECTIONS and j < NUM_PARTICLES) {
        //dont check particles with themselves and if the particle that we want to connect with Ori_id isnt on 0,0
        if (ori_id != j and particles[j].getIsUpdated()) {
            //check if particles distance is on range
            float CheckX = particles[j].getPositionX();
            float CheckY = particles[j].getPositionY();
            float CheckZ = particles[j].getPositionZ();
            if (((CheckX <= orix+(DISTANCE_CONNECTIONS*connectionsModifier)) and (CheckX >= orix-(DISTANCE_CONNECTIONS*connectionsModifier))) and
                ((CheckY <= oriy+(DISTANCE_CONNECTIONS*connectionsModifier)) and (CheckY >= oriy-(DISTANCE_CONNECTIONS*connectionsModifier))) and
                ((CheckZ <= oriz+(DISTANCE_CONNECTIONS*connectionsModifier)) and (CheckZ >= oriz-(DISTANCE_CONNECTIONS*connectionsModifier)))) {
                
                particles[ori_id].addNearParticle(&particles[j]);
                ++counter;
            }
        }
        ++j;
    }
}