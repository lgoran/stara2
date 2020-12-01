// Vaša implementacija (mala izmjena prema prvoj verziji)
#include "score.h"
#include <cstdlib>
#include <string>
#include <iostream>

Score::Score()
{
    if(!mFont.loadFromFile("Gasalt-Regular.ttf")){
        std::cerr << "Ne mogu učitati font: Gasalt-Regular.ttf !" << std::endl;
        std::exit(1);
    }
   // Vaš kod dolazi ovdje
   mScore=0;
   mScoreText.setFont(mFont);
   mScoreText.setPosition(350,150);
   mScoreText.setScale(2,2);
   mScoreText.setString("Score: "+std::to_string(0));
}
void Score::addNoLinesCompleted(int n)
{
  // Vaš kod.
  if(n==0)
    mScore+=0;
  if(n==1){
    mScore+=10;
    }
  if(n==2){
    mScore+=20;}
  if(n==3){
    mScore+=30;}
  if(n==4){
    mScore+=40;}
}
void Score::update()
{
  // Vaš kod.
  mScoreText.setString("Score: " + std::to_string(mScore));
}

void Score::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
  // Vaš kod.
  states.transform *= getTransform();
  target.draw(mScoreText,states);
}
