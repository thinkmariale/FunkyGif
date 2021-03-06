//
//  MyCircles.cpp
//  myGifAnimation
//
//  Created by Mariale Montenegro on 2/5/15.
//
//

#include "MyCircles.h"

MyCircles::MyCircles(ofVec3f pos_, ofColor color_, int r, float timer,int initFrame_, TypeCircle type_)
{
    pos       = pos_;
    color     = color_;
    radius    = r;
    curRadius = radius;
    type = type_;
    
    //window
    amountTimeClosed = timer;
    isClose   = true;
    timeOpen  = 0;
    
    //particles
    initFrame = initFrame_;
    originX   = pos.x;
    originY   = pos.y;

    arrived = false;
    curPoint = 0; //wavepoint
    
}

// function to update windows
void MyCircles::updateStatus()
{
    
    // if NOT closed, check that it has been opened for tiome
    if(!isClose){
        
        if(timeOpen - ofGetElapsedTimef() < 0)
        {
            isClose   = true;
            curRadius = radius;
        }
    }
}

// moving particles on type
void MyCircles::updateParticles(ofVec2f point, float amplitude, float period, float speed)
{
    
    if(type == moveRight)
    {
        pos.x += speed;
        // reset x pos if out of screen
        if(pos.x > ofGetWidth())
            pos.x = -10;
        pos.y += amplitude * cos(TWO_PI * (initFrame - ofGetFrameNum() )/period) ;
    }
    if(type == moveUp)
    {
        pos.y -= speed;
        //reset x pos if out of screen
        if(pos.y <=0)
            pos.y = ofGetHeight() + 10;
        pos.x -= amplitude * cos(TWO_PI * (initFrame - ofGetFrameNum() )/period) ;
        
    }
    if(type == followWayP)
    {
        pos.x -= amplitude * cos(TWO_PI * (initFrame - ofGetFrameNum() )/period) ;
        
        ofVec2f dir = point - pos;  // get direction of vectore by subtracting new pos by cur pos
        dir.normalize();            // normalize vector (scale 1)
        dir = dir*speed;            // scale back vector to appropiate value
        pos += dir;                 // assing vector as velocity
        
        if( (pos - point).length() <=10){
            arrived = true;
        }

    }
    if (type == moveBound)
    {
        // reset x pos if out of screen
         pos.x += speed;
        if(pos.x > ofGetWidth() - ofGetWidth() * 0.2)
            pos.x = ofGetWidth() * 0.4;
        pos.y += amplitude * cos(TWO_PI * (initFrame - ofGetFrameNum() )/period) ;

    }
}

void MyCircles::setOpen(float t,int rad)
{
    timeOpen  = t + amountTimeClosed;
    curRadius = rad;
    isClose   = false;
}
void MyCircles::setClose()
{
    curRadius = radius;
    isClose = true;

}