#ifndef TRACE_HH
#define TRACE_HH

#include <SFML/Graphics.hpp>

class Trace : public sf::Transformable, public sf::Drawable{
private:
  float fDisx,fDisy;
  sf::VertexArray fLines;
  sf::Vector2f fStart,fEnd;
  unsigned long int fPreviousBounce;

  std::vector<sf::VertexArray> fPath;
  std::vector<sf::Color> fColors;
  std::vector<sf::Vector2f> fPathDifference;
  sf::Vector2f fOrigin;

public:
  Trace(float,float,sf::Vector2f);
  ~Trace(){};

  void draw(sf::RenderTarget&, sf::RenderStates) const;
  void UpdateTrace(unsigned long int,sf::Vector2f,bool);
  void TechInfo();
};
#endif
