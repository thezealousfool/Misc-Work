#include <stdio.h>
#include <math.h>

float sqrt_self (float n) {
    float f, df, x;
    x = 1;
    f = x*x - n;
    df = 2*x;
    while (f>=0.00001 || f<=-0.00001) {
        x = x - f/df;
        f = x*x - n;
        df = 2*x;
    }
    return x;
}

float cube_root (float n) {
    float f, df, x;
    x = 1;
    f = x*x*x - n;
    df = 3*x*x;
    while (f>=0.00001 || f<=-0.00001) {
        x = x - f/df;
        f = x*x*x - n;
        df = 3*x*x;
    }
    return x;
}

float x_sinx () {
    float f, df, x;
    x = 1;
    f = x - sin(x);
    df = 1 - cos(x);
    while (f>=0.0000001 || f<=-0.0000001) {
        x = x - f/df;
        f = x - sin(x);
        df = 1 - cos(x);
    }
    return x;
}

int main() {
    float n, result;
    result = sqrt_self(225);
    printf("Square-root of 225: %f\n", result);
    result = sqrt_self(10);
    printf("Square-root of 10: %f\n", result);
    result = cube_root(729);
    printf("Cube-root of 729: %f\n", result);
    result = x_sinx();
    printf("Solution for x = sin(x) is x: %f\n", result);
    return 0;
}