//
//  eval.cpp
//  Homework 2
//
//  Created by Brandon Lo on 1/30/22.
//

#include<string>
#include "Map.h"
#include <iostream>
#include <stack>
using namespace std;

void checkValidity (string infix);
bool makePostfix (string infix, string& postfix);
int solvePostfix (string postfix, const Map& values, int& result);

int evaluate(string infix, const Map& values, string& postfix, int& result){
    if (!makePostfix (infix, postfix)){
        return 1;
    }
    return (solvePostfix(postfix, values, result));
}

int solvePostfix (string postfix, const Map& values, int& result){
    stack<int> operandStack;
    int value = 0;
    char operand2;
    char operand1;
    for (int i = 0; postfix[i]; i++){
        if (isalpha(postfix[i])){
            if (values.get(postfix[i], value) == false){
                return 2;
            }
            operandStack.push(value);
        }
        else{
            int temp = 0;
            operand2 = operandStack.top();
            operandStack.pop();
            operand1 = operandStack.top();
            operandStack.pop();
            if(postfix[i] == '+'){
                temp = operand2 + operand1;
                operandStack.push(temp);
            }
            else if(postfix[i] == '-'){
                temp = operand1 - operand2;
                operandStack.push(temp);
            }
            else if(postfix[i] == '*'){
                temp = operand1*operand2;
                operandStack.push(temp);
            }
            else if(postfix[i] == '/'){
                if (operand2 == 0){
                    return 3;
                }
                temp = operand1/operand2;
                operandStack.push(temp);
            }
        }
    }
    result = operandStack.top();
    return 0;
}

bool makePostfix (string infix, string& postfix){
    int parenCounter = 0;
    int operandCounter = 0;
    bool operatorNext = false;
    bool rParenNext = false;
    bool isOperator = false;
    bool lParenNext = false;
    string temp = "";
    stack<char> operatorStack;
    for (int i = 0; infix[i]; i++){
        switch(infix[i]){
            case 'a':
            case 'b':
            case 'c':
            case 'd':
            case 'e':
            case 'f':
            case 'g':
            case 'h':
            case 'i':
            case 'j':
            case 'k':
            case 'l':
            case 'm':
            case 'n':
            case 'o':
            case 'p':
            case 'q':
            case 'r':
            case 's':
            case 't':
            case 'u':
            case 'v':
            case 'w':
            case 'x':
            case 'y':
            case 'z':
                temp+=infix[i];
                operatorNext = true;
                rParenNext = true;
                lParenNext = true;
                operandCounter++;
                break;
            case '(':
                if (operatorNext == true){
                    return false;
                }
                operatorNext = false;
                lParenNext = true;
                parenCounter++;
                operatorStack.push(infix[i]);
                break;
            case ')':
                if (rParenNext == false){
                    return false;
                }
                lParenNext = false;
                parenCounter--;
                if (parenCounter < 0){
                    return false;
                }
                while (operatorStack.top() != '('){
                    temp += operatorStack.top();
                    operatorStack.pop();
                }
                operatorStack.pop();
                break;
            case '+':
            case '-':
                if (operatorNext == false){
                    return false;
                }
                operatorNext = false;
                isOperator = true;
                rParenNext = false;
                lParenNext = true;
                while (!operatorStack.empty() && operatorStack.top() != '('){
                    temp += operatorStack.top();
                    operatorStack.pop();
                }
                operatorStack.push(infix[i]);
                break;
            case '*':
            case '/':
                if (operatorNext == false){
                    return false;
                }
                operatorNext = false;
                isOperator = true;
                rParenNext = false;
                lParenNext = true;
                while (!operatorStack.empty() && operatorStack.top() != '(' && operatorStack.top() != '+' && operatorStack.top() != '-'){
                    temp += operatorStack.top();
                    operatorStack.pop();
                }
                operatorStack.push(infix[i]);
                break;
        }
    }
    if (parenCounter != 0){
        return false;
    }
    if (operatorNext == false){
        return false;
    }
    if (isOperator == false && operandCounter > 1){
        return false;
    }
    while (!operatorStack.empty()){
        temp += operatorStack.top();
        operatorStack.pop();
    }
    postfix = temp;
    return true;
}

int main()
{
    char vars[] = { 'a', 'e', 'i', 'o', 'u', 'y', '#' };
    int  vals[] = {  3,  -9,   6,   2,   4,   1  };
    Map m;
    for (int k = 0; vars[k] != '#'; k++)
        m.insert(vars[k], vals[k]);
    string pf;
    int answer;
    assert(evaluate("a+ e", m, pf, answer) == 0  &&
                            pf == "ae+"  &&  answer == -6);
    answer = 999;
    assert(evaluate("", m, pf, answer) == 1  &&  answer == 999);
    assert(evaluate("a+", m, pf, answer) == 1  &&  answer == 999);
    assert(evaluate("a i", m, pf, answer) == 1  &&  answer == 999);
    assert(evaluate("ai", m, pf, answer) == 1  &&  answer == 999);
    assert(evaluate("()", m, pf, answer) == 1  &&  answer == 999);
    assert(evaluate("()o", m, pf, answer) == 1  &&  answer == 999);
    assert(evaluate("y(o+u)", m, pf, answer) == 1  &&  answer == 999);
    assert(evaluate("y(*o)", m, pf, answer) == 1  &&  answer == 999);
    assert(evaluate("a+E", m, pf, answer) == 1  &&  answer == 999);
    assert(evaluate("(a+(i-o)", m, pf, answer) == 1  &&  answer == 999);
      // unary operators not allowed:
    assert(evaluate("-a", m, pf, answer) == 1  &&  answer == 999);
    assert(evaluate("a*b", m, pf, answer) == 2  &&
                            pf == "ab*"  &&  answer == 999);
    assert(evaluate("y +o *(   a-u)  ", m, pf, answer) == 0  &&
                            pf == "yoau-*+"  &&  answer == -1);
    answer = 999;
    assert(evaluate("o/(y-y)", m, pf, answer) == 3  &&
                            pf == "oyy-/"  &&  answer == 999);
    assert(evaluate(" a  ", m, pf, answer) == 0  &&
                            pf == "a"  &&  answer == 3);
    assert(evaluate("((a))", m, pf, answer) == 0  &&
                            pf == "a"  &&  answer == 3);
    assert(evaluate("a*e-(o/y)", m, pf, answer) == 0  &&
                            pf == "ae*oy/-"  &&  answer == -29);
    assert(evaluate("a+e-", m, pf, answer) == 1);
    assert(evaluate("a--e", m, pf, answer) == 1);
    assert(evaluate("u*i/a", m, pf, answer) == 0  &&
                            pf == "ui*a/"  &&  answer == 8);;
    answer = 999;
    assert(evaluate("a + t", m, pf, answer) == 2 && pf == "at+" && answer == 999);
    assert(evaluate("a + ?", m, pf, answer) == 1 && answer == 999);
    assert(evaluate("(((a + i))", m, pf, answer) == 1 && answer == 999);
    assert(evaluate(")))a + i(((", m, pf, answer) == 1 && answer == 999);
    assert(evaluate("a + i * 4 - y", m, pf, answer) == 1 && answer == 999);
    assert(evaluate("(a + i)(o - y)", m, pf, answer) == 1 && answer == 999);
    assert(evaluate("(a + i -)", m, pf, answer) == 1 && answer == 999);
    assert(evaluate("(+ a + i)", m, pf, answer) == 1 && answer == 999);
    assert(evaluate("* a + i", m, pf, answer) == 1 && answer == 999);
    assert(evaluate("((a + i) * )", m, pf, answer) == 1 && answer == 999);
    assert(evaluate("((a + i) * u)", m, pf, answer) == 0 && pf == "ai+u*" && answer == 36);
    assert(evaluate("a + i * o - y", m, pf, answer) == 0  && pf == "aio*+y-" && answer == 14);
    assert(evaluate("(((a + i)))", m, pf, answer) == 0  &&  pf == "ai+" && answer == 9);
    assert(evaluate("i/u", m, pf, answer) == 0  &&  pf == "iu/" && answer == 1);
    assert(evaluate("e+a*a", m, pf, answer) == 0  &&  pf == "eaa*+" && answer == 0);
 
}
