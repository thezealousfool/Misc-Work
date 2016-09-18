#include <stdio.h>
#include <math.h>
#define PI 3.1415926
#define W 160
#define H 40

int main() {
    int value, loop;
    float radian, degree, step;
    step = 360.0/W;
    for (loop = 0; loop < H; loop += 1) {
        for (degree = 0; degree <= 360; degree += step){
            radian = degree * PI / 180.0;
            value = (int)(sin(radian)*H/2) + (H/2);
            if (value == loop)
                printf("*");
            else if (loop == (H/2))
                printf("-");
            else
                printf(" ");
        }
        printf("\n");
    }
    return 0;
}