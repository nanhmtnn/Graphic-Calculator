#ifndef SHUNTING_YARD_H
#define SHUNTING_YARD_H

#include <iostream>
#include <cassert>

#include "../queue/MyQueue.h"
#include "../stack/MyStack.h"
#include "../token/token.h"
#include "../token/function.h"
#include "../token/integer.h"
#include "../token/operator.h"
#include "../token/leftparen.h"
#include "../token/rightparen.h"

using namespace std;

class ShuntingYard
{
public:
  // CONSTRUCTORS
  ShuntingYard()
  {
    return;
  }

  ShuntingYard(const Queue<Token*>& input_queue)
  {
    queue = input_queue;
  }

  // save input_q to member variable queue
  void infix(const Queue<Token*>& input_queue)
  {
    queue = input_queue;
  }
  
  // generate postfix queue from infix queue
  Queue<Token*> postfix()
  {
    return shunting_yard();
  }
  Queue<Token*> postfix(const Queue<Token*>& input_queue)
  {
    queue = input_queue;
    return shunting_yard();
  }

  // called by postfix() 
  Queue<Token*> shunting_yard()
  {
    const bool debug = false;
    Queue<Token*> input_queue = queue, output_queue;
    Stack<Token*> op_stack; //operator stack
    while(!input_queue.empty()) {
        switch(input_queue.front()->TypeOf()) {
            case OPERATOR:
                while (!op_stack.empty()) {
                    if (op_stack.top()->TypeOf() == LPAREN) break;
                    else if (op_stack.top()->TypeOf() == FUNCTION || static_cast<Operator*>(input_queue.front())->getOrder() <= static_cast<Operator*>(op_stack.top())->getOrder()
                                                                       && static_cast<Operator*>(input_queue.front())->getOperator() != "^") {
                        output_queue.push(op_stack.top());
                        op_stack.pop();
                    } else break;
                }
            case LPAREN:
                op_stack.push(input_queue.front());
                input_queue.pop();
                break;
            case RPAREN:
                while ((op_stack.top()->TypeOf()) != LPAREN) {
                    output_queue.push(op_stack.top());
                    op_stack.pop();
                }
                input_queue.pop(); // removing rparen
                op_stack.pop(); // removing lparen
                break;
            case FUNCTION:
                if (static_cast<Function*>(input_queue.front())->getFunction() != "X") {
                    while (!op_stack.empty())
                        if (op_stack.top()->TypeOf() == FUNCTION) {
                            output_queue.push(op_stack.top());
                            op_stack.pop();
                        }
                        else break;
                    op_stack.push(input_queue.front());
                    input_queue.pop();
                    break;
                }
            default:
                output_queue.push(input_queue.front());
                input_queue.pop();
                break;
        }
        if (debug) {
            cout << "q_output: " << output_queue << "q_input: " << input_queue;
            if (!op_stack.empty()) cout << "s_operator: " << op_stack;
            cout << endl;
        }
    }


    while(!op_stack.empty()) {
        output_queue.push(op_stack.top());
        op_stack.pop();
    }
    return output_queue;
}

private:
  Queue<Token*> queue;
};

#endif //SHUNTING_YARD_H