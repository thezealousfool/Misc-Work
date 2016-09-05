#include <stdio.h>

int main(void) {
    float x, diff; int loop;
    x = 1.0;
    diff = 1.0;
    for (loop = 1; diff >= 0.00001 || diff <= -0.00001; ++loop) {
        diff = 1 + 1.0/x - x;
        x += diff;
    }
    printf("Converges in %d iterations\n", loop);
    printf("Value of x is %f which is the golden ratio\n", x);
    return 0;
}