#ifndef BALL_HH
#define BALL_HH

#include <SFML/Graphics.hpp>

class Ball : public sf::Transformable, public sf::Drawable{
private:
  float fDisx, fDisy;
  float deg2rad;

  float fMass;
  float fRadius;
  sf::Vector2f fNhat;
  float fVel;
  sf::Vector2f fVelocity;
  sf::Vector2f fPos;

  sf::Color fColor;
  sf::CircleShape fBall;

  float fWallThick;

  static int fCol;
  static int fRow;
  static int fNBalls;

public:
  Ball();
  Ball(float, float, float, float, sf::Color);
  ~Ball() {};
  void draw(sf::RenderTarget&, sf::RenderStates) const;

  void InitializeBall();
  void MoveBall();

  void SetPos(sf::Vector2f a){ fPos = a; }
  void SetNhat(sf::Vector2f a) {fNhat = a; }
  void SetVelocity(sf::Vector2f a){ fVelocity = a; }

  sf::Vector2f GetPos(){ return fPos; }
  float GetRadius(){ return fRadius; }
  float GetMass(){ return fMass; }
  sf::Vector2f GetNhat(){ return fNhat; }
  sf::Vector2f GetVelocity(){ return fVelocity; }

};
#endif
