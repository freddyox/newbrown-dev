//    ************************************************************
//    *                 Brownian Motion Attempt #2               *
//    *                       July   2016                        *
//    ************************************************************
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>

#include <iostream>

#include "../include/Walls.hh"
#include "../include/BallManager.hh"

const float gDisplayx = 500;
const float gDisplayy = 500;

int main() {
  //GAME SETUP
  sf::ContextSettings setting;
  setting.antialiasingLevel = 10;
  sf::RenderWindow window(sf::VideoMode(gDisplayx,gDisplayy), "Brownian Motion",  sf::Style::Default, setting);
  window.setFramerateLimit(60);

  //////////////////////////////////////////////////////
  //                   Parameters                     //
  //////////////////////////////////////////////////////

  Walls walls( window.getSize().x, window.getSize().y );
  walls.makegrid();
  
  BallManager balls(window.getSize().x, window.getSize().y, 3);
  balls.SetWallThick( walls.getWallWidth() );
  balls.Initialize();

  while( window.isOpen() ) {

    sf::Event event;
    while( window.pollEvent(event) ) {
      if( event.type == sf::Event::Closed || sf::Keyboard::isKeyPressed(sf::Keyboard::Escape) ) {
	window.close();
      }
    }

    window.clear(sf::Color::White);

    // UPDATING
    balls.MoveBalls();

    // DRAWINGS
    window.draw(walls);
    window.draw(balls);

    window.display();  
  }
  return 0;
}
