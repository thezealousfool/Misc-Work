#include <stdio.h>

int main(void) {
    int number;
    printf("Enter a number (1-9999): ");
    scanf("%d", &number);
    while (number>0) {
        if (number >= 5000) { printf("N"); number = number - 5000; }
        else if (number >= 1000) { printf("M"); number = number - 1000; }
        else if (number >= 500) { printf("D"); number = number - 500; }
        else if (number >= 100) { printf("C"); number = number - 100; }
        else if (number >= 50) { printf("L"); number = number - 50; }
        else if (number >= 10) { printf("X"); number = number - 10; }
        else if (number >= 5) { printf("V"); number = number - 5; }
        else if (number >= 1) { printf("I"); number = number - 1; }
    }
    printf("\n");
    return 0;
}