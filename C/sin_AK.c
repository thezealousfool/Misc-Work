#include <stdio.h>
#include <math.h>
#define PI 3.1415926

int main(void) {
    int h, half_h, w, r, c;
    int f, g, f2, g2;
    int cycles;
    char tmp;
    float cycle, x, extent;
    //Draw the graph of sin(x).
    //  Display dimensions are w & h
    w = 90; // So, there are 0 to 90, total 91 positions; 45 at the middle.
    h = 30; // So, there are 0 to 30, total 31 positions; 15 at the middle.
    half_h = h / 2;
    cycle = 2 * PI;
    cycles = 1;
    extent = cycles * cycle;
  
    for (r = 0; r <= h; r = r + 1) {
        g = half_h - r; 
        x = 0; c = 0; 
        while (c <= w) {
              f = (int)(half_h * sin(x));
              f2 = (int)(half_h * cos(x));
              if (f == g) printf("*");
              else if (f2 == g) printf("*");
              else if (r!=half_h) printf(" ");
              else printf("-");
               x = x + extent / w; c = c + 1;
        };
	scanf("%c", &tmp);
        printf("\n");
    };

    return 0;
}
