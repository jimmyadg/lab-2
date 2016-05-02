//
//  particle.h
//  story
//
//  Created by James Shih on 4/25/16.
//
//

#ifndef particle_h
#define particle_h

#include "ofMain.h"

//ref:http://openframeworks.cc/ofBook/chapters/OOPs!.html

class James{
    
public:
    void setup();
    void update();
    void draw();
    
    // variables
    float x;        // position
    float y;
    float speedY;   // speed and direction
    float speedX;
    int size;        // size
    int picker;
    ofColor color;  // color using ofColor type
    ofImage james;
    
    James();
private:
};

class Jessie{
    
public:
    void setup();
    void update();
    void draw();
    
    // variables
    float x;        // position
    float y;
    float speedY;   // speed and direction
    float speedX;
    int size;        // size
    int picker;
    ofColor color;  // color using ofColor type
    ofImage jessie;
    
    Jessie();
private:
};

#endif /* particle_h */
