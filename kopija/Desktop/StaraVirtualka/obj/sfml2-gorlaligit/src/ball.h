#pragma once
#include <SFML/Graphics.hpp>

class Ball : public sf::Drawable, public sf::Transformable {
public:
    Ball();
    sf::Vector2f mVelocity;
    void setRadius(float r) { mRadius = r; mCircle.setRadius(r); }
    void setChar(char c) { mChar = c; mText.setString(mChar);}
    float getRadius() const { return mRadius; }
    sf::RectangleShape rect;
    sf::Text mText;

private:
    sf::CircleShape mCircle;
    sf::Font mFont;      
    float mRadius;
    char mChar;

    void draw (sf::RenderTarget &target, sf::RenderStates states) const override;
};




