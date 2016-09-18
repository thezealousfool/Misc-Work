#include <stdio.h>
#include <math.h>

int main(void) {
    int number, loop, number_copy;
    printf("Enter number: ");
    scanf("%d", &number);
    number_copy = number;
    while (number%2 == 0) {
        number = number/2;
        if (number == 1) {
            printf("2\n");
            return 0;
        }
        printf("2*");
    }
    for (loop = 3; loop <= number_copy; loop = loop + 2) {
        while (number%loop == 0) {
            number = number/loop;
            if (number == 1) {
                printf("%d\n", loop);
                break;
            }
            printf("%d*", loop);
        }
    }
    return 0;
}