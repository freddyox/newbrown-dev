#include "../include/Walls.hh"
#include <iostream>

Walls::Walls(float x, float y) {

  displayx = x; 
  displayy = y;
  width = 10.0;
  sf::Color WallColor = sf::Color(51,0,102);

  sf::Vector2f VerticalSize( width, displayy ); 
  Wall.setSize( VerticalSize );
  Wall.setFillColor( WallColor );
  Wall.setPosition( 0, 0);
  WallVec.push_back( Wall );
  Wall.setPosition( displayx-width, 0 );
  WallVec.push_back( Wall );

  sf::Vector2f HorizontalSize( displayx - 2*width, width );
  Wall.setSize( HorizontalSize );
  Wall.setPosition( width, 0 );
  WallVec.push_back( Wall );
  Wall.setPosition( width, displayy-width );
  WallVec.push_back( Wall );

  lines = sf::VertexArray(sf::LinesStrip,2);
}

void Walls::draw(sf::RenderTarget& target, sf::RenderStates) const {
  std::vector<sf::RectangleShape>::const_iterator cit;
  for( cit = WallVec.begin(); cit != WallVec.end(); cit++ )
    target.draw(*cit);

  std::vector<sf::VertexArray>::const_iterator cit1;
  for(cit1=grid.begin(); cit1 != grid.end(); cit1++) {
    target.draw(*cit1);
  }
}

void Walls::makegrid(){
  float totalX = displayx - 2*width;
  float totalY = displayy - 2*width;
  int separation = 20;
  int separationNX = int(totalX) / separation;
  int separationNY = int(totalY) / separation;

  for( int i=1; i<=separationNX; i++ ) {
    // Covers X
    lines[0].position = sf::Vector2f( i*separation, width);
    lines[0].color = sf::Color::Blue;
    lines[1].position = sf::Vector2f( i*separation, displayy - width);
    lines[1].color = sf::Color::Blue;
    grid.push_back( lines );
  }
  for( int i=1; i<=separationNY; i++) {
    // Covers Y
    lines[0].position = sf::Vector2f( width, i*separation );
    lines[0].color = sf::Color::Blue;
    lines[1].position = sf::Vector2f( displayx - width, i*separation );
    lines[1].color = sf::Color::Blue;
    grid.push_back( lines );
  }
}
