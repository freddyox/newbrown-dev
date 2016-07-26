#include "../include/Ball.hh"

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <cmath>
#include <iostream>

int Ball::fCol = -1;
int Ball::fRow = 0;
int Ball::fNBalls = 0;

Ball::Ball(float x, float y, float r, float m, sf::Color color){
  fDisx = x;
  fDisy = y;
  deg2rad = 3.1415 / 180.0;

  fRadius = r;
  fMass = m;
  fColor = color;
  fWallThick = 10.0;

  // Routine to place balls:
  fCol++;
  double xtemp = fDisx - fCol*4.0*fRadius - 2.0 * 10.0;
  double ytemp = fDisy - fRow*4.0*fRadius - 2.0 * 10.0;

  if(xtemp <= 0.0){ 
    fCol = 0; 
    fRow++; 
  }
  if(ytemp>=0.0){
    InitializeBall();
    fNBalls++;
  } else{
    std::cerr << "ERROR: Balls do not fit!" << std::endl;
  }
}

void Ball::InitializeBall(){
  srand(time(NULL)+fNBalls);

  fBall.setRadius( fRadius );
  sf::FloatRect temp = fBall.getLocalBounds();
  fBall.setOrigin( temp.width/2.0, temp.height/2.0 );
  fBall.setFillColor( fColor );

 // Initialize random nhat and velocity:
  float theta = float(rand()%361);
  fNhat = sf::Vector2f( cos(theta*deg2rad), sin(theta*deg2rad) );

  fPos = sf::Vector2f( 3.5*fRadius*(fCol+1), 3.5*fRadius*(fRow+1) );
  fBall.setPosition( fPos );

  fVel = float( rand()%2 + 11 ) / 10.0; //11 - 20
  fVelocity = fVel*fNhat;
}

void Ball::MoveBall(){
  sf::Vector2f pos = fBall.getPosition();

  if( pos.x < fDisx*0.15 || pos.x > 0.85*fDisx ||
      pos.y < fDisy*0.15 || pos.y > 0.85*fDisy ) {
    if( pos.x + fRadius >= fDisx - fWallThick ){
      fVelocity = sf::Vector2f( -fVelocity.x, fVelocity.y );
    }
    if( pos.x - fRadius <= fWallThick ){
      fVelocity = sf::Vector2f( -fVelocity.x, fVelocity.y );
    }
    if( pos.y + fRadius >= fDisy - fWallThick ) {
      fVelocity = sf::Vector2f( fVelocity.x, -fVelocity.y );
    }
    if( pos.y - fRadius <= fWallThick ){
      fVelocity = sf::Vector2f( fVelocity.x, -fVelocity.y );
    }
  }
  fBall.move( fVelocity );
  fPos = fBall.getPosition();
}

void Ball::draw(sf::RenderTarget& target, sf::RenderStates) const {
  target.draw( fBall );
}
