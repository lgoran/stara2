#pragma once
#include <SFML/Graphics.hpp>


// konstruktor: otvaranje prozora i ucitavanje filea

// treba nam fja run koja izvrsava program - osluskuje

class Game
{
public:

    Game();
    void run();

private:

    //prozor nam treba citavo vrijeme izvrsavanja programa pa je zato varijabla clanica klase
    // sprite i texture isto
    sf::RenderWindow   mWindow;
    sf::Texture        mTexture;
    sf::Sprite         mSprite;
    sf::CircleShape    mCircle;
    sf::RectangleShape mRect;

    sf::VertexArray    mVA; // ako zelimo nesto koristiti najlakse nam je to deklarirati kao varijablu clanicu

    sf::Text           mText;
    sf::Font           mFont;  // font koji tekst za ispisivanje uzima, treba nam varijabla za font

    // varijable sluze da prenoisimo info s jednog dijela na drugi
    // ne moramo inicijalizirati u konstruktoru jer smo tu
    bool mLeftPressed  = false;
    bool mRightPressed = false;
    bool mUpPressed    = false;
    bool mDownPressed  = false;

    void procesEvent();
    void update( sf::Time const & dt );
    void render();

};


// klasa koja spaja kuglicu sa slovom da zajedno rotira i ostalo
// moramo preraditi metodu draw da radi ono sto zelimo (ona se nasljeduje iz Drawable)

class Ball : public sf::Drawable, public sf::Transformable
{
public:


private:

    sf::CircleShape mCircle;
    sf::Text        mText;
    sf::Font        mFont;

    void draw( sf::RenderTarget & target, sf::RenderStates states ) const override; // moramo paziti da signatura bude ista kao u baznoj klasi
    // override javlja gresku ako smo slucajno pogrijesili u signaturi prilikom prerade
    // stavljamo draw u privatnu sekciju jer cemo ga koristiti samo pomocu frienda
};
