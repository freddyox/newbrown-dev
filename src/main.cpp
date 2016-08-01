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
#include "../include/Trace.hh"

const float gDisplayx = 500;
const float gDisplayy = 500;

int main() {
  //GAME SETUP
  sf::ContextSettings setting;
  setting.antialiasingLevel = 10;
  sf::RenderWindow window(sf::VideoMode(gDisplayx,gDisplayy), "Brownian Motion",  sf::Style::Default, setting);
  window.setFramerateLimit(60);
  sf::RenderWindow tracerwindow(sf::VideoMode(gDisplayx,gDisplayy), "Brownian Motion - Tracers");
  tracerwindow.setFramerateLimit(60);

  //////////////////////////////////////////////////////
  //                   Parameters                     //
  //////////////////////////////////////////////////////

  Walls walls( window.getSize().x, window.getSize().y );
  walls.makegrid();
  
  BallManager balls(window.getSize().x, window.getSize().y, 3);
  balls.SetWallThick( walls.getWallWidth() );
  balls.Initialize();

  // This should be the unique balls initial position:
  Trace trace(window.getSize().x, window.getSize().y, balls.GetUniqueBallPos() );

  long unsigned int click = 0;

  while( window.isOpen() && tracerwindow.isOpen() ) {

    sf::Event event;
    while( window.pollEvent(event) ) {
      if( event.type == sf::Event::Closed || sf::Keyboard::isKeyPressed(sf::Keyboard::Escape) ) {
	window.close();
      }
    }
    while( tracerwindow.pollEvent(event) ) {
      if( event.type == sf::Event::Closed || sf::Keyboard::isKeyPressed(sf::Keyboard::Escape) ) {
	tracerwindow.close();
      }
    }
    
    window.clear(sf::Color::White);
    tracerwindow.clear(sf::Color::Black);

    // UPDATING
    balls.MoveBalls();
    trace.UpdateTrace(balls.GetNBounces(), balls.GetUniqueBallPos(),balls.DidBallHitWall());

    // DRAWINGS
    window.draw(walls);
    window.draw(balls);
    //tracerwindow.draw(walls);
    tracerwindow.draw( trace );

    window.display();  
    tracerwindow.display();
  }
  trace.TechInfo();
  return 0;
}
