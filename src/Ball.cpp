#include "../include/Ball.hh"

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <cmath>
#include <iostream>

int Ball::fNBalls = 0;

Ball::Ball(float x, float y, sf::Vector2f pos_i, float r, float m, sf::Color color){
  fDisx = x;
  fDisy = y;
  deg2rad = 3.1415 / 180.0;

  fRadius = r;
  fMass = m;
  fColor = color;
  fWallThick = 10.0;

  fPos = pos_i;
  InitializeBall();
  fNBalls++;

  fHitWall = false;
}

void Ball::InitializeBall(){
  srand(time(NULL)+fNBalls);

  fBall.setRadius( fRadius );
  fBall.setOutlineThickness( -0.1*fRadius );
  fBall.setOutlineColor( sf::Color::Black );
  sf::FloatRect temp = fBall.getLocalBounds();
  fBall.setOrigin( temp.width/2.0, temp.height/2.0 );
  fBall.setFillColor( fColor );

 // Initialize random nhat and velocity:
  float theta = float(rand()%361);
  fNhat = sf::Vector2f( cos(theta*deg2rad), sin(theta*deg2rad) );

  fBall.setPosition( fPos );

  fVel = float( rand()%2 + 11 ) / 10.0; //11 - 20
  fVelocity = fVel*fNhat;
}

void Ball::SetColor(sf::Color col){
  fBall.setFillColor(col);
}

void Ball::MoveBall(){
  sf::Vector2f pos = fBall.getPosition();
  fHitWall = false;
  // Initial Check:
  if( pos.x < fDisx*0.15 || pos.x > 0.85*fDisx ||
      pos.y < fDisy*0.15 || pos.y > 0.85*fDisy ) {
    // Check for boundary collision:
    if( pos.x + fRadius >= fDisx - fWallThick ){
      fVelocity = sf::Vector2f( -fVelocity.x, fVelocity.y );
      fHitWall = true;
    }
    if( pos.x - fRadius <= fWallThick ){
      fVelocity = sf::Vector2f( -fVelocity.x, fVelocity.y );
      fHitWall = true;
    }
    if( pos.y + fRadius >= fDisy - fWallThick ) {
      fVelocity = sf::Vector2f( fVelocity.x, -fVelocity.y );
      fHitWall = true;
    }
    if( pos.y - fRadius <= fWallThick ){
      fVelocity = sf::Vector2f( fVelocity.x, -fVelocity.y );
      fHitWall = true;
    }
  }
  // Then update the ball:
  fBall.move( fVelocity );
  fPos = fBall.getPosition();
}

void Ball::draw(sf::RenderTarget& target, sf::RenderStates) const {
  target.draw( fBall );
}
