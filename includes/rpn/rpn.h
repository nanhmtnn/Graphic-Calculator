#ifndef RPN_H
#define RPN_H

#include <iostream>
#include <cmath>

#include "../queue/MyQueue.h"
#include "../stack/MyStack.h"
#include "../token/token.h"
#include "../token/function.h"
#include "../token/integer.h"
#include "../token/operator.h"
#include "../token/leftparen.h"
#include "../token/rightparen.h"

using namespace std;

class RPN
{
public:
  // CTOR
  RPN();

  RPN(const Queue<Token*>& input_queue)
  {
    queue = input_queue;
  }
  
  // save input_q to member variable queue
  void set_input(const Queue<Token *> &input_queue)
  {
    queue = input_queue;
  }

  // return result from member variable queue
  double operator()(double value = 0)
  {
    Queue<Token*> _queue = queue;
    Stack<double> _stack;
    string _operator;
    string _function;
    double a, b;

    while (_queue.empty() == false)
    {
      if      (_queue.front()->TypeOf() == INTEGER) 
      {
        _stack.push(static_cast<Integer*>(_queue.front())->getValue());
        _queue.pop();
      }
      else if (_queue.front()->TypeOf() == OPERATOR)
      {
        b = _stack.top();
        _stack.pop();

        a = _stack.top();
        _stack.pop();

        _operator = static_cast<Operator*>(_queue.front())->getOperator();
        _queue.pop();

        if      (_operator == "+") _stack.push(a + b);
        else if (_operator == "-") _stack.push(a - b);
        else if (_operator == "*") _stack.push(a * b);
        else if (_operator == "/") _stack.push(a / b); 
        else if (_operator == "^") _stack.push(pow(a, b));

      }
      else if (_queue.front()->TypeOf() == FUNCTION)
      {
        _function = static_cast<Function*>(_queue.front())->getFunction();
        _queue.pop();

        if (_function == "X" || _function == "x") _stack.push(value);
        else 
        {
          double getTop = _stack.top();
          _stack.pop();

          if      (_function == "sin" )   _stack.push(sin (getTop));
          else if (_function == "cos" )   _stack.push(cos (getTop));
          else if (_function == "tan" )   _stack.push(tan (getTop));
          else if (_function == "arcsin") _stack.push(acos(getTop));
          else if (_function == "arccos") _stack.push(acos(getTop));
          else if (_function == "arctan") _stack.push(atan(getTop));
          else if (_function == "log")    _stack.push(log(getTop));
          else if (_function == "sqrt")   _stack.push(sqrt(getTop));
          else if (_function == "abs")    _stack.push(abs(getTop));
        }
      }
    }
    return _stack.top();
  }

  // called by operator ()
  double rpn(double value = 0);

private:
  Queue<Token*> queue;

};

#endif //RPN_H