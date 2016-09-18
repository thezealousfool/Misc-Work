#include <stdio.h>

float x_power_n (float x, int n) {
    float temp;
    if (n == 1)
        return x;
    if (n%2 == 0) {
        temp = x_power_n(x, n/2);
        return temp*temp;
    }
    else {
        return x*x_power_n(x, n-1);
    }
}

int main() {
    float x, result; int n;
    printf("Enter base: ");
    scanf("%f", &x);
    printf("Enter exponent: ");
    scanf("%d", &n);
    result = x_power_n(x, n);
    printf("%f ^ %d = %f\n", x, n, result);
    return 0;
}