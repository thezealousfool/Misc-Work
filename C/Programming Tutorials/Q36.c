#include <stdio.h>
#include <math.h>

struct pair {
    float value; int iterations;
};

struct pair ln_1_plus_x (float x) {
    float term, sum; int loop;
    struct pair ret_val;
    sum = 0.0; term = x;
    for (loop = 1; term >= 0.00001 || term <= -0.00001; ++loop) {
        term = pow(-1, loop+1)*pow(x, loop)/loop;
        sum += term;
    }
    ret_val.value = sum; ret_val.iterations = loop;
    return ret_val;
}

struct pair e_power_x (float x) {
    float term, sum; int loop;
    struct pair ret_val;
    sum = 1.0; term = 1.0;
    for (loop = 1; term >= 0.00001 || term <= -0.00001; ++loop) {
        term = term * x / loop;
        sum += term;
    }
    ret_val.value = sum; ret_val.iterations = loop + 1;
    return ret_val;
}

int main() {
    struct pair ln_self, exp_self;
    ln_self = ln_1_plus_x (1.0);
    exp_self = e_power_x (ln_self.value);
    printf("Calculated ln(1+x) for x = 1 is: %8.4f\n", ln_self.value);
    printf("Verification: e ^ %8.4f is: %8.4f\n", ln_self.value, exp_self.value);
    printf("\n\nlog takes %d iterations\n exp takes %d iterations\n", ln_self.iterations, exp_self.iterations);
    if (exp_self.iterations < ln_self.iterations)
        printf("\n\nExponentiation converges faster\n");
    else if (ln_self.iterations < exp_self.iterations)
        printf("\n\nLogarithm converges faster\n");
    else
        printf("\n\nBoth Logarithm and Exponentiation are equally fast\n");
}