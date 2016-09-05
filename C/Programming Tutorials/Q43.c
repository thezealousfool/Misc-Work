#include <stdio.h>
#include <math.h>
#define W 40
#define H 40

int main(void) {
    char screen[H][W];
    int center_x, center_y, radius, x, y;
    center_x = 20; center_y = 15;
    radius = 9;
    for (y=0; y<H; ++y) {
        for (x=0; x<W; ++x) {
            screen[y][x] = ' ';
        }
    }
    for (x = -radius; x <= radius; ++x) {
        y = sqrt((radius - abs(x))*(radius + abs(x)));
        if (x+center_x>=0 && x+center_x<W && center_y-y>=0 && center_y-y<H) {
            screen[x+center_x][center_y-y] = '*';
        }
        if (x+center_x>=0 && x+center_x<W && center_y+y>=0 && center_y+y<H) {
            screen[x+center_x][center_y+y] = '*';
        }
    }
    for (y=0; y<H; ++y) {
        for (x=0; x<W; ++x) {
            printf("%c", screen[y][x]);
        }
        printf("\n");
    }
}