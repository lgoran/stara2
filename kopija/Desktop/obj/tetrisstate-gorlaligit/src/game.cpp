#include "game.h"
#include "playstate.h"
#include <array>
#include <iostream>

Game::Game() : mWindow(sf::VideoMode(800,800), "Tetris"), mGameSpeed(3.0f),
               mGameScore(0)
{
    // Inicijalizacija stanja dolazi ovdje
    mAllStates[0]=new WelcomeState(this);
    mAllStates[1]=new PlayState(this);
    mAllStates[2]=new SpeedState(this);
    setState(GameState::Welcome);
}

Game::~Game()
{
   // Eventualna dealokacija  
}

void Game::run(){
    
    sf::Clock clock;
    sf::Time  protekloVrijeme = sf::Time::Zero;
    while(mWindow.isOpen()){
        processEvents();
        sf::Time dt = sf::seconds(1.0/mGameSpeed);
        protekloVrijeme+=clock.restart();
        if(mpGameState == mAllStates[GameState::State::Playing])
        {
            if(protekloVrijeme>=dt)
            {
                update();
                protekloVrijeme=sf::Time::Zero;
            }
        }
        else update();
        render();
    }
}

void Game::setState(GameState::State st)
{
    mpGameState = mAllStates[st];
    mpGameState->start();
}

sf::RenderWindow * Game::getWindow()
{
    return &mWindow;
}

void Game::processEvents()
{
    sf::Event event;
    while(mWindow.pollEvent(event))
    {
        if(event.type == sf::Event::Closed)
            mWindow.close();
        else if(event.type ==sf::Event::Resized){
            // Spriječi deformaciju objekata prilikom promjene veličine prozora
            sf::FloatRect viewRect(0, 0, event.size.width, event.size.height);
            mWindow.setView(sf::View(viewRect));
        }
        else {
            mpGameState->handleEvents(event);
		}
    }
}

void Game::update()
{
    mpGameState->update();
}

void Game::render()
{
     mWindow.clear();
     mpGameState->render();
     mWindow.display();
}
