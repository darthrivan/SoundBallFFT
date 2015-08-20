//
//  Particle.cpp
//  SoundBall
//
//  Created by blag on 11/08/15.
//
//

//#include <GLUT/glut.h>
//#include <cmath>

//#include "ofMath.h"
//#include "ofGraphics.h"
#include "Particle.h"


Particle::Particle() {
    theta = 0;
    u = 0;
    vTheta = 0;
    vU = 0;
    x = y = z = 0.0;
    near = vector<Particle*>();
    partSizeModi = 0.0;
    isUpdated = false;
}

Particle::Particle(float _theta, float _u, float radius) {
    theta = _theta;
    u = _u;
    vTheta = 0;
    vU = 0;
    x = y = z = 0.0;
    partSizeModi = 1.;
    isUpdated = false;
    //update(radius);
}

float Particle::getPositionX() {
    return this->x;
}

float Particle::getPositionY() {
    return this->y;
}

float Particle::getPositionZ() {
    return this->z;
}

void Particle::copyParticle(Particle p){
    this->theta = p.theta;
    this->u = p.u;
    this->vTheta = p.vTheta;
    this->vU = p.vU;
    this->x = p.x;
    this->y = p.y;
    this->z = p.z;
    this->partSizeModi = p.partSizeModi;
    this->near = p.near;
}

void Particle::copyParticleConnections(Particle p){
    this->near = p.near;
}

void Particle::addNearParticle(Particle* pa){
    near.push_back(pa);
}

int Particle::getNumberNearParticles(){
    return near.size();
}

bool Particle::getIsUpdated(){
    return isUpdated;
}

void Particle::setPartSizeModi(float p){
    partSizeModi = p;
}

void Particle::updateRadius(float radius, float modifier){
    if (!isUpdated) isUpdated = true;
    x = radius*cos(theta)*sqrt(1-(u*u))*modifier;
    y = radius*sin(theta)*sqrt(1-(u*u))*modifier;
    z = radius*u*modifier;
}

void Particle::update(float radius) {
    if (!isUpdated) isUpdated = true;
    vTheta += ofRandom(-0.001,0.001);
    theta += vTheta;
    
    if (theta<0||theta>TWO_PI) {
        vTheta*=-1;
    }
    
    vU += ofRandom(-0.001,0.001);
    u += vU;
    
    if (u<-1||u>1) vU*=-1;
    
    vU *= 0.95;
    vTheta *= 0.95;
    
    x = radius*cos(theta)*sqrt(1-(u*u));
    y = radius*sin(theta)*sqrt(1-(u*u));
    z = radius*u;
}

void Particle::draw() {
    ofPushMatrix();
    ofCircle(x, y, z, 0.2*partSizeModi);
    ofPopMatrix();
    //Now we draw the connections
    for (int i = 0; i < near.size(); ++i) {
        ofSetColor(255, 255, 255);
        ofSetLineWidth(1);
        //ofLine(origin, end);
        ofLine(this->x, this->y, this->z,
               (*near[i]).getPositionX(), (*near[i]).getPositionY(), (*near[i]).getPositionZ());
    }
}