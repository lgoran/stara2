#include "playstate.h"


// Vaš kod.
#include "game.h"

PlayState::PlayState(Game * pGame) : GameState(pGame)
{
    // Vaš kod dolazi ovdje (ako bude potrebe). 
    mBoard.setSpeed(pGame->mGameSpeed); 
    
}
void PlayState::start()
{
    mScore.mScore=0;
    mBoard.clearState();
    mBoard.setSpeed(mpGame->mGameSpeed);
    mBoard.spawnPiece();
}
void PlayState::handleEvents(sf::Event event)
{
    if(event.type == sf::Event::KeyPressed)
        {
            // Vaš kod dolazi ovdje !!!  
            if(event.key.code==sf::Keyboard::Left)
                mBoard.update(-20,0); 
            if(event.key.code==sf::Keyboard::Right)
                mBoard.update(20,0);
            if(event.key.code==sf::Keyboard::R || event.key.code==sf::Keyboard::Up)
                mBoard.update(0,0);
            if(event.key.code==sf::Keyboard::Down)
                {
                    mBoard.update(0,20);
                    mScore.addNoLinesCompleted(mBoard.getNoLinesCompleted());
                    mScore.update();
                } 
            if(event.key.code==sf::Keyboard::Space)
            {
                mBoard.spaceDown();
                mScore.addNoLinesCompleted(mBoard.getNoLinesCompleted());
                mScore.update();
            }
        }
}

void PlayState::update()
{
   // Updatiranje scene. Vaš kod dolazi ovdje
   mpGame->mGameScore = mScore.getScore();
   if(mBoard.isGameOver())
   {
       mpGame->setState(Speed);
   }
   else{
        mBoard.update(0,20);
        mScore.addNoLinesCompleted(mBoard.getNoLinesCompleted());
        mScore.update();
   }
}

void PlayState::render()
{
     mpGame->getWindow()->draw(mBoard);
     mpGame->getWindow()->draw(mScore);
}

