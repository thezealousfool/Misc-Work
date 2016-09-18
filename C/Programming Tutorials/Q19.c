#include <stdio.h>

void swap_value (int a, int b) {
    int temp = a;
    a = b;
    b = temp;
    printf("Inside call by value function:\n");
    printf("After swapping:\ta: %d\tb: %d\n\n", a, b);
}

void swap_reference (int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
    printf("Inside call by reference function:\n");
    printf("After swapping:\ta: %d\tb: %d\n\n", *a, *b);
}

int main() {
    int a, b;
    a = 5; b = 10;
    printf("Inside main function:\n");
    printf("a: %d\tb: %d\n\n", a, b);
    swap_value(a, b);
    printf("Inside main function:\n");
    printf("a: %d\tb: %d\n\n", a, b);
    swap_reference(&a, &b);
    printf("Inside main function:\n");
    printf("a: %d\tb: %d\n\n", a, b);
    return 0;
}