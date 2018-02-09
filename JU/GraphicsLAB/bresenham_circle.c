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

void bresenham_circle(int x, int y, int r) {
    int p = 0, q = r, d = 3 - 2 * r;
    while (p < q) {
        _draw_circle(x, y, p, q);
        p += 1;
        if (d < 0) {
            d += 4*p + 6;
        } else {
            q -= 1; d += 4*(p-q) + 10;
        }
    };
    _draw_circle(x, y, p, q);
}

int main() {
    int gd = DETECT, gm;
    initgraph(&gd, &gm, NULL);
    drawgrid();
    bresenham_circle(2, -9, 20);
    delay(5000);
    closegraph();
    return 0;
}