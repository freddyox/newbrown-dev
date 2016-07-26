#include "../include/BallManager.hh"
#include <iostream>
#include <cmath>
#include <string>

BallManager::BallManager(float x, float y, int N){
  fDisx = x;
  fDisy = y;

  fBalls = 25;

  fBallToWatch = int(fBalls/2);
  fNBounces = 0;

  // These are temporary just to make the balls identical. But they 
  // do not need to be identical...
  fRadius = 20.0;
  fMass = 2.0;
}

void BallManager::Initialize(){
  sf::Color col;
  for(int i=0; i<fBalls; i++){
    col = ((i==fBallToWatch) ? sf::Color::Red : sf::Color::Blue);
    Ball ball( fDisx, fDisy, fRadius, fMass, col);
    fBallVec.push_back( ball );
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

      // Check for overlaps - There can be a check before the
      // vector calculation.
      if (ball1_pos.x + 1.2*r1 + r2 > ball2_pos.x 
	  && ball1_pos.x < ball2_pos.x + 1.2*r1 + r2
	  && ball1_pos.y + 1.2*r1 + r2 > ball2_pos.y 
	  && ball1_pos.y < ball2_pos.y + 1.2*r1 + r2) {

	sf::Vector2f dis = ball2_pos - ball1_pos;
	float mag = sqrt(dis.x*dis.x + dis.y*dis.y);
	if( mag< (r1+r2)*1.01 ) {
	  collided = true;
	}
	if( collided ) {
	  if(i==fBallToWatch||j==fBallToWatch){ 
	    fNBounces++;
	    std::cout << fNBounces << std::endl;
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
