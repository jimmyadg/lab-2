//
//  particle.cpp
//  story
//
//  Created by James Shih on 4/25/16.
//
//

#include "particle.h"
James::James(){
}

void James::setup(){
    x = ofRandom(0, ofGetWidth());      // give some random positioning
    y = ofRandom(0, ofGetHeight());
    speedX = ofRandom(-3, 3);           // and random speed and direction
    speedY = ofRandom(-3, 3);
    james.load("james.png");
    size = ofRandom(20,100);
    
    color.set(255,255,255);
}

void James::update(){
    if(x < 0 ){
        x = 0;
        speedX *= -1;
    } else if(x > ofGetWidth()){
        x = ofGetWidth();
        speedX *= -1;
    }
    
    if(y < 0 ){
        y = 0;
        speedY *= -1;
    } else if(y > ofGetHeight()){
        y = ofGetHeight();
        speedY *= -1;
    }
    
    x+=speedX;
    y+=speedY;
}

void James::draw(){
    ofSetColor(color);
    james.draw(x,y,size,size);
}

Jessie::Jessie(){
}

void Jessie::setup(){
    x = ofRandom(0, ofGetWidth());      // give some random positioning
    y = ofRandom(0, ofGetHeight());
    speedX = ofRandom(-3, 3);           // and random speed and direction
    speedY = ofRandom(-3, 3);
    jessie.load("jessie.png");
    size = ofRandom(20,100);
    
    color.set(255,255,255);
}

void Jessie::update(){
    if(x < 0 ){
        x = 0;
        speedX *= -1;
    } else if(x > ofGetWidth()){
        x = ofGetWidth();
        speedX *= -1;
    }
    
    if(y < 0 ){
        y = 0;
        speedY *= -1;
    } else if(y > ofGetHeight()){
        y = ofGetHeight();
        speedY *= -1;
    }
    
    x+=speedX;
    y+=speedY;
}

void Jessie::draw(){
    ofSetColor(color);
    jessie.draw(x,y,size,size);
}