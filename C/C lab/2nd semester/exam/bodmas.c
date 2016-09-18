#include <stdio.h>

int greater_precedence (char c1, char c2) {
    switch (c2) {
        case '*' : 
        case '/' : return 0;
        case '-' :
        case '+' : if (c1!='+' && c1!='-' && c1!='(') {
                            return 1;
                        }
                        else {
                            return 0;
                        }
    }
    return 0;
}

double calculate_value (char* postfix, int* index) {
    double left_value, right_value;
    char choice;
    if (postfix[*index] >= '0' && postfix[*index] <= '9') {
        --*index;
        return postfix[*index + 1] - '0';
    }
    choice = postfix[*index];
    --*index;
    right_value = calculate_value(postfix, index);
    left_value = calculate_value(postfix, index);
    if (choice == '+') {
        return left_value + right_value;
    }
    if (choice == '-') {
        return left_value - right_value;
    }
    if (choice == '*') {
        return left_value * right_value;
    }
    if (choice == '/') {
        return left_value / right_value;
    }
    return 0;
}

int main () {
    char infix[101], postfix[101], operators[101], temp;
    int infix_index, postfix_index, operator_index;
    double value;
    infix_index = postfix_index = operator_index = 0;

    // taking input

    printf("Enter expression: ");
    scanf("%100[^\n]", infix);

    //converting to postfix from infix

    while (infix[infix_index] != '\0') {
        temp = infix[infix_index];
        if (temp >= '0' && temp<='9') {
            postfix[postfix_index] = temp;
            ++infix_index;
            ++postfix_index;
            continue;
        }
        if (temp == '(') {
            operators[operator_index] = temp;
            ++operator_index;
            ++infix_index;
            continue;
        }
        if (temp == ')') {
            --operator_index;
            while (operator_index>=0 && operators[operator_index] != '(') {
                postfix[postfix_index] = operators[operator_index];
                ++postfix_index;
                --operator_index;
            }
            ++infix_index;
            continue;
        }
        operators[operator_index] = temp;
        while (operator_index>0 && greater_precedence(operators[operator_index-1], operators[operator_index])==1) {
            postfix[postfix_index] = operators[operator_index-1];
            ++postfix_index;
            operators[operator_index-1] = operators[operator_index];
            --operator_index;
        }
        ++infix_index;
        ++operator_index;
    }
    --operator_index;
    while (operator_index>=0) {
        postfix[postfix_index] = operators[operator_index];
        ++postfix_index;
        --operator_index;
    }
    postfix[postfix_index] = '\0';
    printf("%s\n", postfix);
    // calculating result from postfix 

    --postfix_index;
    value = calculate_value (postfix, &postfix_index);
    printf("Value of the expression : %lf\n", value);

    return 0;
}