#include <iostream>
#include <stack>
#include <string>
#include <vector>
#include <sstream>

using namespace std;

bool isOperator(char input)
{
    switch (input) {
    case '+':
    case '-':
    case '*':
    case '%':
    case '/':
    case '^':
        return true;
    default:
        return false;
    }
}

int Prec(char input)
{
    switch (input) {
    case '+':
    case '-':
        return 2;
    case '*':
    case '%':
    case '/':
        return 3;
    case '^':
        return 6;
    case '(':
        return 1;
    }
}
bool isOperand(char input)
{
    if (isalpha(input) || isdigit(input))
        return true;
    return false;
}

string infixToPostfix(string input) {
    stack<char> opstack;
    string output;

    for (int i{ 0 }; i < input.size(); i++) {
        if (isOperand(input[i])) {
            output += input[i];
        }
        else if (input[i] == '(') {
            opstack.push(input[i]);
        }
        else if (input[i] == ')') {
            char popped{ opstack.top() };
            opstack.pop();
            while (popped != '(') {
                output += popped;
                popped = opstack.top();
                opstack.pop();
            }
        }
        else if (isOperator(input[i])) {
            while (!opstack.empty() && Prec(opstack.top()) >= Prec(input[i])) {
                output += opstack.top();
                opstack.pop();
            }
            opstack.push(input[i]);
        }
    }

    while (!opstack.empty()) {
        output += opstack.top();
        opstack.pop();
    }

    return output;
}
double performMathOperation(char opp, double first, double second) {
    switch (opp) {
    case '+' :
        return first + second;
    case '-':
        return first - second;
    case '*':
        return first * second;
    case '/':
        return first / second;
    }
}
double evaluteExpression(string expression) {
    string postfix = infixToPostfix(expression);

    stack<double> opperands;
    for (int i = 0; i < postfix.size(); i++) {
        if (isdigit(postfix[i])) {
            opperands.push(stod(string(1, postfix[i])));
        }
        else if (isOperator(postfix[i])) {
            double second = opperands.top();
            opperands.pop();
            double first = opperands.top();
            opperands.pop();
            double result = performMathOperation(postfix[i], first, second);
            opperands.push(result);
        }
    }
    return opperands.top();
}

int main() {
	string expression;
	cout << "enter expression(infix)(single digit numbers only): ";
	cin >> expression;

	cout << "result: " << evaluteExpression(expression) << endl;

}