#ifndef STR_TO_INFIX_H
#define STR_TO_INFIX_H

#include <string>

#include "../queue/MyQueue.h"
#include "../stack/MyStack.h"
#include "../token/token.h"
#include "../token/function.h"
#include "../token/integer.h"
#include "../token/operator.h"
#include "../token/leftparen.h"
#include "../token/rightparen.h"

Queue<Token*> strToInfix(string input) {
    int leftParentCount=0, rightParentCount=0;
    const bool debug = false;
    auto lowerCase = [&](string s) {
        for(int i = 0; i < s.size(); ++i) {
            if ('A' <= s[i] && s[i] <= 'Z') {
                s[i] = tolower(s[i]);
            }
        }
        return s;
    };
    string str = lowerCase(input);
    if (debug) std::cout << str << std::endl;
    Queue<Token*> infix;
    for (int i=0; i<str.length(); i++) {
        string word;
        switch (str[i]) {
            case '0' ... '9':
                word.clear();
                while (i<str.length()&&str[i]=='.'||str[i]>='0'&&str[i]<='9'){
                    word+=str[i++];
                }
                i--;
                infix.push(new Integer(stod(word)));
                break;

            case '-':
                if (i+1 < str.length() && '0' <= str[i+1] && str[i+1] <= '9') { // negative number;
                    // First check if this is inside a function
                    if (i-1 >= 0) {
                        if (str[i-1] != '(') {
                            infix.push(new Operator("+"));
                        }
                    }
                    word += str[i++];
                    while (i < str.length() && str[i] == '.' || '0' <= str[i] && str[i] <= '9') {
                        word += str[i++];
                    }
                    i--;

                    infix.push(new Integer(stod(word)));
                    break;
                }
            case '+':
            case '*':
            case '/':
            case '^':
                word += str[i];
                if (debug) std::cout << word << std::endl;
                infix.push(new Operator(word));
                break;
            case '(':
                infix.push(new LeftParen);
                leftParentCount++;
                break;
            case ')':
                infix.push(new RightParen);
                rightParentCount++;
                break;
            case 'a' ... 'z':
                while ((str[i]>='a'&&str[i]<='z')) {
                    word+=str[i++];
                }
                i--;
                if (debug) std::cout << word << std::endl;
                if (word == "max") {
                    infix.push(new Operator("@"));
                } else if (word == "min") {
                    infix.push(new Operator("#"));
                } else {
                    infix.push(new Function(word));
                }
                break;
            default:
                //return Queue<Token*>();
                break;
        }
        if (debug) std::cout << infix; 
    }
    for(auto it: infix) cout << it << " ";
    cout << '\n';
    if (leftParentCount == rightParentCount) return infix;
    else return Queue<Token*>();
}

#endif //STR_TO_INFIX