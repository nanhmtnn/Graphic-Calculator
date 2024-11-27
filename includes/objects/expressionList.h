#ifndef HOVERABLE_TEXT_H
#define HOVERABLE_TEXT_H

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

#include "../constants/windowConstants.h"


class expressionList 
{
    public:

    expressionList(sf::Font& newFont, sf::String str="", sf::Color color = sf::Color(255,255,255), sf::Vector2f pos = sf::Vector2f(0,0));
    expressionList(const expressionList& other);
    expressionList& operator=(const expressionList& RHS);

    void setText(sf::String str) {text.setString(str);}
    sf::String getText() {return text.getString();}
    void setColor(sf::Color color) {text.setFillColor(color);}
    sf::Color getColor() {return text.getFillColor();}

    void draw(sf::RenderWindow& window);

    private:
    sf::Text text;
};

expressionList::expressionList(sf::Font& font, sf::String str, sf::Color color, sf::Vector2f pos) 
{
    text.setPosition(pos);
    text.setString(str);
    text.setFillColor(color);
    text.setFont(font);
    std::cout << static_cast<std::string>(text.getString()) << " " << text.getPosition().x << ", " << text.getPosition().y << std::endl;
}

void expressionList::draw(sf::RenderWindow& window) 
{
    window.draw(text);
}


expressionList::expressionList(const expressionList& other) 
{
    text = other.text;
}

expressionList& expressionList::operator=(const expressionList& RHS) 
{
    text = RHS.text;
    return *this;
}

#endif //HOVERABLE_TEXT_H