#include <iostream>
#include <stack>
#include <string>

bool greater_precedence (char c1, char c2) {
    switch (c2) {
        case '*' :
        case '/' : return false;
        case '+' :
        case '-' : if (c1 != '+' && c1 != '-' && c1 != '(') return true;
            else return false;
    }
    return false;
}

std::string to_postfix (std::string& infix) {
    std::size_t index = 0;
    char temp;
    std::stack<char> stack;
    std::string postfix;
    while (index < infix.length()) {
        temp = infix[index];
        if (temp >= '0' && temp <= '9') {
            postfix += temp;
        }
        else if (temp == '(') {
            stack.push(temp);
        }
        else if (temp == ')') {
            while (stack.size() > 0) {
                temp = stack.top(); stack.pop();
                if (temp == '(')
                    break;
                else
                    postfix += temp;
            }
        }
        else {
            while (stack.size() > 0 && greater_precedence(stack.top(), temp)) {
                postfix += stack.top(); stack.pop();
            }
            stack.push(temp);
        }
        ++index;
    }
    while (stack.size() > 0) {
        postfix += stack.top(); stack.pop();
    }
    return postfix;
}

double evaluate_postfix (std::string& postfix) {
    std::stack<double> stack;
    std::size_t index = 0;
    char temp;
    while (index < postfix.length()) {
        temp = postfix[index];
        if (temp >= '0' && temp <= '9') {
            stack.push(temp - '0');
        }
        else {
            double right = stack.top(); stack.pop();
            double left = stack.top(); stack.pop();
            switch (temp) {
                case '+' : stack.push(left+right); break;
                case '-' : stack.push(left-right); break;
                case '*' : stack.push(left*right); break;
                case '/' : stack.push(left/right); break;
            }
        }
        ++index;
    }
    return stack.top();
}

int main() {
    std::cout << "Enter expression: ";
    std::string infix;
    std::getline(std::cin, infix);
    std::string postfix = to_postfix(infix);
    std::cout << postfix << "\n";
    double value = evaluate_postfix(postfix);
    std::cout << "Value: " << value << "\n";
    return 0;
}