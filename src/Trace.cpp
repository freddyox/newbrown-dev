#include "../include/Trace.hh"
#include <iostream>
#include <cmath>
#include <fstream>

Trace::Trace(float x, float y, sf::Vector2f start){
  fDisx = x;
  fDisy = y;

  fStart = start;
  fOrigin = fStart;

  fColors.push_back( sf::Color::Red );
  fColors.push_back( sf::Color(255, 127, 0) );
  fColors.push_back( sf::Color(255, 255, 0) );
  fColors.push_back( sf::Color(0, 255, 0) );
  fColors.push_back( sf::Color(0, 0, 255) );
  fColors.push_back( sf::Color(75, 0, 130) );
  fColors.push_back( sf::Color(148,0,211) );
  fPreviousBounce = 0;

  fLines = sf::VertexArray(sf::LinesStrip,2);

}

void Trace::draw( sf::RenderTarget& target, sf::RenderStates) const {
  std::vector<sf::VertexArray>::const_iterator cit;
  for(cit=fPath.begin(); cit != fPath.end(); cit++) {
    target.draw(*cit);
  }
}

void Trace::UpdateTrace(unsigned long int bounce, sf::Vector2f end, bool hitwall){
  fEnd = end;
  if( fPreviousBounce != bounce ) {
    fPathDifference.push_back( fEnd - fStart );
    fLines[0].position = fStart;
    fLines[0].color = fColors[fPreviousBounce%fColors.size()];
    fLines[1].position = fEnd;
    fLines[1].color = fColors[fPreviousBounce%fColors.size()];
    fPreviousBounce++;
    fPath.push_back( fLines );
    fStart = fEnd;
  }
  if( hitwall ){
    fPathDifference.push_back( fEnd - fStart );
    fLines[0].position = fStart;
    fLines[0].color = fColors[fPreviousBounce%fColors.size()];
    fLines[1].position = fEnd;
    fLines[1].color = fColors[fPreviousBounce%fColors.size()];
    fPath.push_back( fLines );
    fStart = fEnd;
  }
}

void Trace::TechInfo(){
  std::vector<sf::Vector2f>::iterator it;
  float deltax = 0.0;
  float deltay = 0.0;
  float total_distance = 0.0;
  
  std::ofstream output;
  output.open("output.txt");

  for(it=fPathDifference.begin(); it!=fPathDifference.end(); it++){
    sf::Vector2f v = *it;
    deltax += v.x;
    deltay += v.y;
    float mag = sqrt(v.x*v.x + v.y*v.y);
    output << mag << std::endl;
    total_distance += mag;
  }

  std::cout << "Starting Location = " << "(" << fOrigin.x << ", "
	    << fOrigin.y << ")" << std::endl;
  std::cout << "Delta X from origin = " << deltax << std::endl;
  std::cout << "Delta Y from origin = " << deltay << std::endl;

  std::cout << "Total Length of trip = " << total_distance << std::endl;
  std::cout << "Average distance traveled before collision = " 
	    << total_distance / fPath.size() << std::endl;
}
