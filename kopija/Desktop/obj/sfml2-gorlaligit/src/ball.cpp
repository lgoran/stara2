#include "game.h"
#include <random>
// Ovdje dolazi vaš kod.
static char slovo='A';
Ball::Ball(){
    mChar=slovo;
    mFont.loadFromFile("Comfortaa-Bold.ttf");
    mText.setFont( mFont );
    mText.setColor(sf::Color::Green);
    mText.setString(mChar);
    mText.setCharacterSize( 10 );
    mText.setOrigin(rect.getOrigin());
    mText.setScale(2,2);
    mCircle.setFillColor(sf::Color(0,0,255,128));
    ++slovo;
}
void Ball::draw(sf::RenderTarget &target, sf::RenderStates states ) const
{
    states.transform *= getTransform();
    target.draw( mText, states );
    target.draw( mCircle, states );

}