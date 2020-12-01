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
  mLevel=1;
  mLevelText.setFont(mFont);
   mLevelText.setPosition(350,300);
   mLevelText.setScale(2,2);
   mLevelText.setString("Level: "+std::to_string(1));

}
int Score::getLevel()
{
  return mLevel;
}
void Score::addNoLinesCompleted(int n)
{
  // Vaš kod.
  if(n==0)
    mScore+=0;
  if(n==1){
    if(mScore%50>=40)
      mLevel++;
    mScore+=10;
    }
  if(n==2){
    if(mScore%50>=30)
      mLevel++;
    mScore+=20;}
  if(n==3){
    if(mScore%50>=20)
      mLevel++;
    mScore+=30;}
  if(n==4){
    if(mScore%50>=10)
      mLevel++;
    mScore+=40;}
  
}

void Score::setGameOver()
{
  // Vaš kod.
  mScoreText.setString("Game Over");
}

void Score::update()
{
  // Vaš kod.
  mScoreText.setString("Score: " + std::to_string(mScore));
  mLevelText.setString("Level: " + std::to_string(mLevel));
}

void Score::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
  // Vaš kod.
  states.transform *= getTransform();
  target.draw(mScoreText,states);
  target.draw(mLevelText,states);
}
