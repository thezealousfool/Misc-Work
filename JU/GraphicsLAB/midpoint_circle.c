#include <graphics.h>
#include <math.h>

#define SCRW    640
#define SCRH    480

#define STEPS   8

#define relx(x) (((x) + MAXX) * STEPS)
#define rely(y) ((MAXY - (y)) * STEPS)

#define MAXX    (floor(SCRW/(STEPS*1.0)) / 2)
#define MAXY    (floor(SCRH/(STEPS*1.0)) / 2)

#define max(x,y)    ((x) > (y) ? (x) : (y))

void drawgrid() {
    for (int i = 0; STEPS * i <= SCRW; ++i) {
        line(STEPS * i, 0, STEPS * i, SCRH);
    }
    for (int i = 0; STEPS * i <= SCRH; ++i) {
        line(0, STEPS * i, SCRW, STEPS * i);
    }
}

void plotpoint(int x, int y) {
    if (abs(x) >= MAXX || abs(y) >= MAXY)
        return;
    int arr[10] = {relx(x), rely(y), relx(x+1), rely(y), relx(x+1), rely(y+1), relx(x), rely(y+1), relx(x), rely(y)};
    fillpoly(5, arr);
}

void _draw_circle(int x, int y, int p, int q) {
    plotpoint(x+p, y+q);
    plotpoint(x-p, y+q);
    plotpoint(x+p, y-q);
    plotpoint(x-p, y-q);
    plotpoint(x+q, y+p);
    plotpoint(x-q, y+p);
    plotpoint(x+q, y-p);
    plotpoint(x-q, y-p);
}

void midpoint_circle(int x, int y, int r) {
    int x0 = 0, y0 = r, h = 1 - r;
    while (x0 < y0) {
        _draw_circle(x, y, x0, y0);
        if (h < 0) {
            h += 2*x0 + 3;
        } else {
            h += 2*(x0-y0) + 5;
            y0--;
        }
        x0++;
    };
    _draw_circle(x, y, x0, y0);
}

int main() {
    int gd = DETECT, gm;
    initgraph(&gd, &gm, NULL);
    drawgrid();
    midpoint_circle(2, 9, 20);
    delay(5000);
    closegraph();
    return 0;
}