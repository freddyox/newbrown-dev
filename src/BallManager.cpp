#include "../include/BallManager.hh"
#include <iostream>
#include <cmath>
#include <string>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

BallManager::BallManager(float x, float y, int N){
  fDisx = x;
  fDisy = y;

  fBalls = 90;

  srand(time(NULL));
  fBallToWatch = rand()%fBalls;
 
  fNBounces = 0;

  // These are temporary just to make the balls identical. But they 
  // do not need to be identical...
  fRadius = 6.0;
  fMass = 2.0;

  fColors.push_back( sf::Color::Red );
  fColors.push_back( sf::Color(255, 127, 0) );
  fColors.push_back( sf::Color(255, 255, 0) );
  fColors.push_back( sf::Color(0, 255, 0) );
  fColors.push_back( sf::Color(75, 0, 130) );
  fColors.push_back( sf::Color(148,0,211) );
}

void BallManager::Initialize(){
  sf::Color color;
  srand(time(NULL));
  // A scheme to place balls of diff radius, etc..
  float dontmakeittooclose = 0.0;
  if( fRadius <= 10.0 ) {
    dontmakeittooclose = 4.5;
  } else if( fRadius > 10.0 && fRadius <= 15.0 ){
    dontmakeittooclose = 2.0;
  } else if( fRadius > 15.0 && fRadius <= 25 ) {
    dontmakeittooclose = 1.0;
  } else{
    dontmakeittooclose = 0.5;
  }
  if( dontmakeittooclose < 0.1 ){
    dontmakeittooclose = 1.5;
  }

  // Let's calculate how many balls can fit in x/y directions:
  int NBallsX = int( (fDisx-2.0*10.0) / (2.0*fRadius + dontmakeittooclose*fRadius) );
  int NBallsY = int( (fDisy-2.0*10.0) / (2.0*fRadius + dontmakeittooclose*fRadius) );

  // Make a grid:
  float offX = fDisx / NBallsX;
  float offY = fDisy / NBallsY;

  int row=1;
  int col=1;
  for(int i=0; i<fBalls; i++){
    color = (i==fBallToWatch) ? fColors[rand()%fColors.size()] : sf::Color::Blue;

    sf::Vector2f ballpos(10.0 + offX*col, 10.0 + offY*row);
    if( col<= NBallsX && row <= NBallsY ) {
      if( ballpos.x + fRadius < fDisx-10.0 && ballpos.x - fRadius > 10.0 &&
	  ballpos.y + fRadius < fDisy-10.0 && ballpos.y - fRadius > 10.0 ) {
	Ball ball( fDisx, fDisy, ballpos, fRadius, fMass, color );
	fBallVec.push_back( ball );
      }
    }
    // The lattice
    col++;
    if( col==NBallsX ) {
      row++;
      col=1;
    }
  }
  // If our random ball accidentally doesn't get placed due to 
  // the cuts, then we should reset it - not sure how often this
  // will occur.
  if( fBallToWatch > fBallVec.size() ) {
    std::cerr << "Careful! Ball did not make it in the display which means something"
	      << " is up with the cuts / routin to place balls!" << std::endl;
    fBallToWatch = rand()%(fBallVec.size());
    fBallVec[fBallToWatch].SetColor( fColors[rand()%fColors.size()] );
  }
}

void BallManager::MoveBalls(){
  for(fIt=fBallVec.begin(); fIt!=fBallVec.end(); fIt++){
    fIt->MoveBall();
  }
  Collision();
}

void BallManager::draw(sf::RenderTarget& target, sf::RenderStates) const {
  std::vector<Ball>::const_iterator cit;
  for(cit=fBallVec.begin(); cit!=fBallVec.end(); cit++){
    target.draw( *cit );
  }
}

void BallManager::Collision(){
 
  for(int i=0; i<fBalls; i++){
    
    sf::Vector2f ball1_pos = fBallVec[i].GetPos();
    float r1 = fBallVec[i].GetRadius();
    
    for(int j=i+1; j<=fBalls; j++){
      bool collided = false;
      
      sf::Vector2f ball2_pos = fBallVec[j].GetPos();
      float r2 = fBallVec[j].GetRadius();

      // Check for overlaps first using simple rectangular cuts
      if (ball1_pos.x + 1.2*r1 + r2 > ball2_pos.x 
	  && ball1_pos.x < ball2_pos.x + 1.2*r1 + r2
	  && ball1_pos.y + 1.2*r1 + r2 > ball2_pos.y 
	  && ball1_pos.y < ball2_pos.y + 1.2*r1 + r2) {

	sf::Vector2f dis = ball2_pos - ball1_pos;
	float mag = sqrt(dis.x*dis.x + dis.y*dis.y);
	// Radial cut:
	if( mag < (r1+r2)*1.01 ) {
	  collided = true;
	}
	// Handle elastic collision:
	if( collided ) {
	  if(i==fBallToWatch||j==fBallToWatch){ 
	    fNBounces++;
	  }
	  sf::Vector2f v1 = fBallVec[i].GetVelocity();
	  sf::Vector2f v2 = fBallVec[j].GetVelocity();
	  float m1 = fBallVec[i].GetMass();
	  float m2 = fBallVec[j].GetMass();

	  float v1x_p = ( v1.x*(m1-m2) + (2.0*m2*v2.x) ) / (m1+m2);
	  float v1y_p = ( v1.y*(m1-m2) + (2.0*m2*v2.y) ) / (m1+m2);
	  float v2x_p = ( v2.x*(m2-m1) + (2.0*m1*v1.x) ) / (m1+m2);
	  float v2y_p = ( v2.y*(m2-m1) + (2.0*m1*v1.y) ) / (m1+m2);
	  
	  fBallVec[i].SetVelocity(sf::Vector2f(v1x_p, v1y_p));
	  fBallVec[j].SetVelocity(sf::Vector2f(v2x_p, v2y_p));
	}
      }
    }
  }
}

sf::Vector2f BallManager::GetUniqueBallPos(){
  return fBallVec[fBallToWatch].GetPos();
}

bool BallManager::DidBallHitWall(){
  return fBallVec[fBallToWatch].DidItHitWall();
}
