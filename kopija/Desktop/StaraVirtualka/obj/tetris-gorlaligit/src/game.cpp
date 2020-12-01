#include "game.h"

Game::Game() : mWindow(sf::VideoMode(800,800), "Tetris")
{
    // Vaš kod dolazi ovdje (ako bude potrebe).   
}

void Game::run(){
    mBoard.spawnPiece();
    float vrime=0.3;
    sf::Clock clock;
    sf::Time  protekloVrijeme = sf::Time::Zero;
    sf::Time dt = sf::seconds(0.5);
    while(mWindow.isOpen()){
        processEvents();
        protekloVrijeme+=clock.restart();
        if(protekloVrijeme>=dt)
        {
            update();
            protekloVrijeme=sf::Time::Zero;
        }
        render();
        dt=sf::seconds(0.5-mScore.getLevel()*0.05f);
    }
}

void Game::processEvents()
{
    sf::Event event;
    while(mWindow.pollEvent(event))
    {
        switch(event.type)
        {
        case sf::Event::Closed:
            mWindow.close();
            break;

        case sf::Event::KeyPressed:
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
	    break;
        case sf::Event::Resized:
            // Spriječi deformaciju objekata prilikom promjene veličine prozora
            sf::FloatRect viewRect(0, 0, event.size.width, event.size.height);
            mWindow.setView(sf::View(viewRect));
            break;
        }
    }
}

void Game::update()
{
   // Updatiranje scene. Vaš kod dolazi ovdje
   if(mBoard.isGameOver())
   {
       mScore.setGameOver();
   }
   else{
        mBoard.update(0,20);
        mScore.addNoLinesCompleted(mBoard.getNoLinesCompleted());
        mScore.update();
   }
}

void Game::render()
{
     mWindow.clear();


     mWindow.draw(mBoard);
     mWindow.draw(mScore);

     mWindow.display();
}
