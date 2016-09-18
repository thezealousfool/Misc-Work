#include <stdio.h>

int gcd (int a, int b) {
    if (a == 0)
        return b;
    return gcd(b%a, a);
}

int main() {
    int number1, number2;
    printf("Enter 2 numbers:\n");
    scanf("%d %d", &number1, &number2);
    printf("GCD is: %d\n", gcd(number1, number2));
}