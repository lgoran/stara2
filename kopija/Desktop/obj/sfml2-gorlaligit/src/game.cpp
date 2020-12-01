#include "game.h"
#include <random>
#include <memory>
// Ovdje dolazi vaš kod
float skalarni_produkt(sf::Vector2f vec1,sf::Vector2f vec2)
{
    return vec1.x*vec2.x+vec1.y*vec2.y;
}
Game::Game(): mWindow(sf::VideoMode(800,800),"Odbijanje loptica")
{
    mRectangle.setSize(sf::Vector2f(600,600));
    mRectangle.setPosition(100,100);
    mRectangle.setOutlineColor(sf::Color::Red);
    mRectangle.setOutlineThickness(5.0f);

}
void Game::run()
{
    initPositions(10,20.0);
    initVelocity(100);
    sf::Clock clock;
    sf::Time  protekloVrijeme = sf::Time::Zero;
    sf::Time dt = sf::seconds( 1.00/60.f );
    while( mWindow.isOpen() )
    {
        processEvents();
        protekloVrijeme += clock.restart();
        while( protekloVrijeme >= dt )
        {
            protekloVrijeme -= dt;
            update( dt );
        }
        render();
    }
}
void Game::processEvents()
{

    sf::Event event;
    while ( mWindow.pollEvent( event ) )
    {
        switch( event.type )
        {
            case sf::Event::Closed:
                mWindow.close();
            break;
        }
    }
}
void Game::update(sf::Time dt)
{
    for (size_t i = 0; i < mBall.size(); i++)
    {
        mBall[i]->move(mBall[i]->mVelocity.x*dt.asSeconds(),mBall[i]->mVelocity.y*dt.asSeconds());
        checkForCollisionsWithWalls(mBall[i].get(),dt);
        checkForCollisionsWithBalls(mBall[i].get(),dt);
        mBall[i]->mText.rotate(2.0*dt.asSeconds());
        mBall[i]->mText.setPosition(mBall[i]->getOrigin()-sf::Vector2f(10,10));
    }    
}
void Game::render()
{
    mWindow.clear();
    mWindow.draw(mRectangle);
    for (size_t i = 0; i < mBall.size(); i++)
    {
        mWindow.draw(*mBall[i]);
    }  
    mWindow.display();
}
void Game::initPositions(std::size_t nBalls, float radius)
{
    std::uniform_real_distribution<double> distribution(100.0 +radius,700.0-radius);
    for (size_t i = 0; i < nBalls; i++)
    {
        std::unique_ptr<Ball> ball(new Ball());
        ball->setRadius(radius);
        ball->setOrigin(std::sqrt(2)*radius,std::sqrt(2)*radius);
        ball->mText.setOrigin(5,5);
        do{
            ball->setPosition(distribution(mRand),distribution(mRand));
        }while(jeli_se_preklapa(ball.get()));        
        mBall.push_back(std::move(ball));
    }    
}
void Game::initVelocity(float maxVel)
{
    std::normal_distribution<double> distribution(0.0,100.0);
    for (size_t i = 0; i < mBall.size(); i++)
    {
        do{
            mBall[i]->mVelocity.x=distribution(mRand);
            mBall[i]->mVelocity.y=distribution(mRand);
        }while(mBall[i]->mVelocity.x * mBall[i]->mVelocity.x + mBall[i]->mVelocity.y * mBall[i]->mVelocity.y >maxVel*maxVel);
    }
}
void Game::checkForCollisionsWithWalls(Ball * pball, sf::Time dt) const
{
    sf::Vector2f pos=pball->getPosition();
    if(pball->getPosition().x<=105+pball->getRadius() || pball->getPosition().x>=705-pball->getRadius())
        pball->mVelocity.x=-pball->mVelocity.x;
    pball->setPosition (pos + pball->mVelocity * dt.asSeconds ());
    if(pball->getPosition().y<=105+pball->getRadius() || pball->getPosition().y>=705-pball->getRadius())
        pball->mVelocity.y=-pball->mVelocity.y;
    pball->setPosition (pos + pball->mVelocity * dt.asSeconds ());    
}
void Game::checkForCollisionsWithBalls(Ball * pball, sf::Time dt) const
{
    for (auto &ball : mBall) {
        if (ball.get () == pball) {
            continue;
        }
        if (skalarni_produkt (pball->getPosition () - ball->getPosition(),pball->getPosition () - ball->getPosition()) >= 2 * ball->getRadius () * 2 * ball->getRadius ()) {
            continue;
        }
        sf::Vector2f v1 = ball->mVelocity;
        sf::Vector2f v2 = pball->mVelocity;
        sf::Vector2f x1 = ball->getPosition ();
        sf::Vector2f x2 = pball->getPosition ();
        ball->mVelocity = v1 - skalarni_produkt (v1 - v2, x1 - x2) / skalarni_produkt(x1 - x2,x1 - x2) * (x1 - x2);
        pball->mVelocity = v2 - skalarni_produkt (v2 - v1, x2 - x1) / skalarni_produkt(x2 - x1, x2-x1) * (x2 - x1);
        ball->setPosition (ball->getPosition () + ball->mVelocity * dt.asSeconds ());
        pball->setPosition (pball->getPosition () + pball->mVelocity * dt.asSeconds ());
        return;
    }
}

bool Game::jeli_se_preklapa(Ball * ball) const
 {
     for (size_t i = 0; i < mBall.size(); i++)
     {
         if(ball->getPosition()==mBall[i]->getPosition()) i++;
         if(i==mBall.size()) break;
         if((ball->getPosition().x - mBall[i]->getPosition().x)*(ball->getPosition().x - mBall[i]->getPosition().x) +
         (ball->getPosition().y - mBall[i]->getPosition().y)*(ball->getPosition().y- mBall[i]->getPosition().y) <= 4*ball->getRadius()*ball->getRadius())
         return true;
     }
     return false;
 }