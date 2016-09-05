#include <stdio.h>
#include <math.h>
#define PI 3.1415926

float sin_cos_tan_series (float theta, char c) {
    float sum, term;
    int term_number;
    if (c == 's')
        term = theta;
    if (c == 'c')
        term = 1;
    sum = 0.0;
    term_number = 1;
    if (c == 't') {
        sum = sin_cos_tan_series (theta, 's');
        sum = sum / sin_cos_tan_series (theta, 'c');
        return sum;
    }
    while (term >= 0.000001 || term <= -0.000001) {
        sum += term;
        ++term_number;
        if (c == 's')
            term = term * (-1*theta*theta) / ((term_number*2 - 1)*(term_number*2 - 2));
        if (c == 'c')
            term = term * (-1*theta*theta) / ((term_number*2 - 2)*(term_number*2 - 3));
    }
    return sum;
}

int main(void) {
    int degree; float theta;
    printf("     x      \tsin(series) \tsin(library)\tcos(series) \tcos(library)\ttan(series) \ttan(library)\n");
    for (degree = 0; degree <= 360; degree = degree + 10) {
        theta = degree * PI / 180;
        printf("\t%3d\t\t\t%9.5f\t\t%9.5f\t\t%9.5f\t\t%9.5f\t\t%9.5f\t\t%9.5f\n", degree, sin_cos_tan_series(theta, 's'), sin(theta), sin_cos_tan_series(theta, 'c'), cos(theta), sin_cos_tan_series(theta, 't'), tan(theta));
    }
    return 0;
}