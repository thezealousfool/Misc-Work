#include <stdio.h>

int main(void) {
    float sum, one_by_n, n;
    int loop;
    printf("\tn\t\tn times 1/n\n");
    for (n = 1; n <= 100; n = n+1) {
        one_by_n = 1.0 / n;
        sum = one_by_n;
        for (loop = 1; loop < n; loop = loop+1)
            sum = sum + one_by_n;
        printf("%7.2f\t\t%f\n", n, sum);
    }
    return 0;
}