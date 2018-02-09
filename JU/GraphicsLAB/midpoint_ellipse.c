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

void _draw_ellipse(int x, int y, int p, int q) {
    plotpoint(x+p, y+q);
    plotpoint(x-p, y+q);
    plotpoint(x+p, y-q);
    plotpoint(x-p, y-q);
}

void midpoint_ellipse(int xc, int yc, int a, int b) {
    int x, y, p, pe, ps, pse, pe2, ps2, pse2, b2, a2;
    x = 0; y = b;
    b2 = b*b; a2 = a*a;
    p = b2 + (a2*(1-4*b) - 2)/4;
    pe = 3*b2;
    pe2 = 2*b2;
    pse = pe - 2*a2*(b-1);
    pse2 = pe2 + 2*a2;
    _draw_ellipse(xc, yc, x, y);
    while (pse < (2*a2 + 3*b2)) {
        if (p < 0) {
            p += pe;
            pe += pe2;
            pse += pe2;
        } else {
            p += pse;
            pe += pe2;
            pse += pse2;
            --y;
        }
        ++x;
        _draw_ellipse(xc, yc, x, y);
    }
    p -= (a2*(4*y - 3) + b2*(4*x + 3) + 2)/4;
    ps = a2*(3-2*y);
    pse = 2*b2 + 3*a2;
    ps2 = 2*a2;
    while (y > 0) {
        if (p > 0) {
            p += pe;
            pe += ps2;
            pse += ps2;
        } else {
            p += pse;
            pe += ps2;
            pse += pse2;
            ++x;
        }
        --y;
        _draw_ellipse(xc, yc, x, y);
    }
}

int main() {
    int gd = DETECT, gm;
    initgraph(&gd, &gm, NULL);
    drawgrid();
    midpoint_ellipse(2, 9, 20, 10);
    delay(5000);
    closegraph();
    return 0;
}