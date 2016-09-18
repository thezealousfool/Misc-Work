#include <stdio.h>

void fib (unsigned int a, unsigned int b, unsigned int terms, float* golden) {
    if (terms == 0) {
        *golden = 1.0*b/a;
        return;
    }
    printf("%d ", b);
    fib (b, a+b, terms-1, golden);
}

int main(void) {
    unsigned int terms;
    float golden = 0.0;
    printf("Enter number of terms: ");
    scanf("%u", &terms);
    if (terms > 0) {
        printf("1 ");
        fib(1, 1, terms-1, &golden);
        printf("\n");
    }
    printf("Golden Number: %f\n", golden);
    return 0;
}