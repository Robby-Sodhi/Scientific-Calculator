#include <iostream>
#include <stack>
#include <string>
#include <vector>

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

vector<string> infixToPostfix(string input) {
    stack<char> opstack;
    vector<string> output;

    for (int i{ 0 }; i < input.size(); i++) {
        if (isOperand(input[i])) {
            string digit = string(1, input[i]);
            while (isOperand(input[i + 1])) {
                digit += input[i + 1];
                ++i;
            }
            output.push_back(digit);
        }
        else if (input[i] == '(') {
            opstack.push(input[i]);
        }
        else if (input[i] == ')') {
            char popped{ opstack.top() };
            opstack.pop();
            while (popped != '(') {
                output.push_back(string(1, popped));
                popped = opstack.top();
                opstack.pop();
            }
        }
        else if (isOperator(input[i])) {
            while (!opstack.empty() && Prec(opstack.top()) >= Prec(input[i])) {
                output.push_back(string(1, opstack.top()));
                opstack.pop();
            }
            opstack.push(input[i]);
        }
    }

    while (!opstack.empty()) {
        output.push_back(string(1, opstack.top()));
        opstack.pop();
    }

    return output;
}
double performMathOperation(string opp, double first, double second) {
    if (opp.compare("+") == 0)
        return first + second;
    else if (opp.compare("-") == 0)
        return first - second;
    else if (opp.compare("*") == 0)
        return first * second;
    else if (opp.compare("/") == 0)
        return first / second;
    else if (opp.compare("^") == 0)
        return pow(first, second);

}
double evaluteExpression(string expression) {
    vector<string> postfix = infixToPostfix(expression);

    //postfix to infix with evaluation
    stack<double> opperands;
    for (int i = 0; i < postfix.size(); i++) {

        try {
            double integer = stod(postfix[i]);
            opperands.push(integer);
        }
        catch (std::invalid_argument& e) {
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
    cout << "good example expressions: " << endl;
    cout << "(128 * (85 * 26 - 11) / 19) = 14814.3" << endl;
    cout << "10*150/1000+50 = 51.5" << endl;
    cout << "18238*231895*21941/100000000 = 927951" << endl;
    cout << "enter expression(infix)(no variables): ";
    getline(cin, expression);

    cout << "result: " << evaluteExpression(expression) << endl;

}