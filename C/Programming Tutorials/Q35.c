#include <stdio.h>
#include <math.h>

int main() {
    float x, value, term;
    int loop;
    x = 0.57735; // tan (PI/6)
    value = 0.0;
    term = x;
    for (loop=0; term >=0.00001 || term <= -0.00001; ++loop) {
        term = pow(-1,loop)*pow(x, 2*(loop+1)-1)/(2*(loop+1)-1);
        value = value + term;
    }
    printf("Value of PI: %f\nNo of iterations: %d\n", value*6, loop);
    return 0;
}