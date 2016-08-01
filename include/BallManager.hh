#ifndef BALLMANAGER_HH
#define BALLMANAGER_HH

#include <SFML/Graphics.hpp>

#include "../include/Ball.hh"

#include <vector>

class Ball;

class BallManager : public sf::Drawable, public sf::Transformable{
private:
  float fDisx, fDisy;
  float fWallThick;

  float fRadius;
  float fMass;

  int fBalls;
  long unsigned int fNBounces;
  int fBallToWatch;
  std::vector<Ball> fBallVec;
  std::vector<Ball>::iterator fIt;

  std::vector<sf::Color> fColors;
    
public:
  BallManager(float,float,int);
  ~BallManager() {};
  void draw(sf::RenderTarget&, sf::RenderStates) const;

  void Initialize();
  void MoveBalls();
  void Collision();

  void SetWallThick(float a){ fWallThick = a; }
  sf::Vector2f GetUniqueBallPos();
  bool DidBallHitWall();
  long unsigned int GetNBounces(){ return fNBounces; }
};
#endif
