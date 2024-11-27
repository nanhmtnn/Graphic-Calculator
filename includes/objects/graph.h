#ifndef GRAPH_H
#define GRAPH_H

#include <vector>
#include <cmath>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

#include "../expression/expression.h"
#include "../str_to_infix/str_to_infix.h"
#include "../constants/windowConstants.h"
#include "../plot/plot.h"
#include "../point/point.h"
#include "../random/random.h"
#include "../queue/MyQueue.h"
#include "../objects/SidePanel.h"



class Graph 
{
    public:
    Graph(sf::Font& newFont);

    void plot();
    void reset();
    void draw(sf::RenderWindow& window);
    void addExpression(std::string str);

    SidePanel* sidePanel;

    sf::View view;
    sf::CircleShape origin;
    sf::RectangleShape background;
    sf::Font font;
    
    vector<Expression> expressions;
    vector<sf::CircleShape> dots;
    vector<sf::RectangleShape> lines;
    vector<sf::RectangleShape> axis;

    int rangeX;
    int rangeY;
     
    float scale = 1;
};

Graph::Graph(sf::Font& newFont) 
{
    font = newFont;

    view.reset(sf::FloatRect(0,0, SCREEN_WIDTH*GRAPH_WIDTH_RATIO, SCREEN_HEIGHT));
    view.setViewport(sf::FloatRect(0,0,GRAPH_WIDTH_RATIO,1));

    origin = sf::CircleShape(5);
    origin.setOrigin(origin.getRadius(), origin.getRadius());
    origin.setPosition(view.getSize()/2.f);

    background.setSize(view.getSize());
    background.setFillColor(graphColor);
}

void Graph::plot() 
{
    reset();
    float lower_bound = (-origin.getPosition().x)/CONST_SCALE*scale;
    float upper_bound = (view.getSize().x-origin.getPosition().x)/CONST_SCALE*scale;
    for (int i=0; i<expressions.size(); i++) 
    {   
        Queue<Point> points = PlotExpression(expressions[i].postfix, lower_bound, upper_bound, (upper_bound-lower_bound)/res);

        if(points.empty()) return;

        for (Queue<Point>::Iterator it = points.begin(); it!=points.end(); it++) 
        {
            sf::CircleShape circle(2);
            circle.setPosition(sf::Vector2f(origin.getPosition().x+it->getVector().x*CONST_SCALE/scale, origin.getPosition().y-it->getVector().y*CONST_SCALE/scale));
            circle.setFillColor(expressions[i].color);
            dots.push_back(circle);
        }
    }
}
    

void Graph::reset() {
    lines.clear();
    dots.clear();
}

void Graph::draw(sf::RenderWindow& window) {
    window.setView(view);
    window.draw(background);

    for (int i=0; i<axis.size(); i++) {
        window.draw(axis[i]);
    }
    for (int i=0; i<dots.size(); i++) {
        if (background.getGlobalBounds().contains(dots[i].getPosition()))
            window.draw(dots[i]);
    }
    for (int i=0; i<lines.size(); i++) {
        window.draw(lines[i]);
    }

}


void Graph::addExpression(std::string str) 
{
    Queue<Token*> q = strToInfix(str);
    if (!q.empty()) {
        expressions.emplace_back(str);
        sidePanel->addExpression(expressions.back());
        reset();
        plot();
    }
}


#endif // GRAPH_H