#ifndef EXPRESSION_H
#define EXPRESSION_H


#include <vector>

#include "../point/point.h"
#include "../str_to_infix/str_to_infix.h"

#include "../shunting_yard/shunting_yard.h"
#include "../rpn/rpn.h"

#include "../random/random.h"

#include "../queue/MyQueue.h"
#include "../stack/MyStack.h"

#include "../token/token.h"
#include "../token/function.h"
#include "../token/integer.h"
#include "../token/operator.h"
#include "../token/leftparen.h"
#include "../token/rightparen.h"
#include "../token/constants.h"


class Expression 
{
    public:
        friend class Graph;
        Expression(std::string str);
        void setExpression(std::string str);
        std::string getExpression() {return infixStr;}
        sf::Color getColor() {return color;}
        void setColor(sf::Color newColor) {color = newColor;}

    private:
        vector<Point> points;
        Queue<Token*> postfix;
        bool linear;
        float slope;
        std::string infixStr;
        sf::Color color;
};

Expression::Expression(std::string str) 
{
    color = sf::Color(fastrand(255), fastrand(255), fastrand(255));
    setExpression(str);
}

void Expression::setExpression(std::string str) 
{
    infixStr = str;
    Queue<Token*> infix = strToInfix(str);
    ShuntingYard sy(infix);
    postfix = sy.postfix();
}


#endif // EXPRESSION_H