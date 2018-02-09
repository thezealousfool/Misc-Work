#include <graphics.h>
#include <math.h>

#define SCRW    640
#define SCRH    480

#define STEPS   10

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

void bresenham_line(int x1, int y1, int x2, int y2, int invert_axis) {
    if (abs(y2 - y1) > abs(x2 - x1)) {
        bresenham_line(y1, x1, y2, x2, 1);
        return;
    }
    if (x1 > x2) {
        int temp = x2;
        x2 = x1;
        x1 = temp;
        temp = y2;
        y2 = y1;
        y1 = temp;
    }
    int dy = (y2-y1) < 0 ? -1 : 1;
    int new_m = 2 * (y2 - y1) * dy;
    int new_slope_error = new_m - (x2 - x1);
    for (int x = x1, y = y1; x <= x2; ++x)
    {
        if (invert_axis)
            plotpoint(y, x);
        else
            plotpoint(x, y);
        new_slope_error += new_m;
        if (new_slope_error >= 0)
        {
            y += dy;
            new_slope_error  -= 2 * (x2 - x1);
        }
    }
}

int main() {
    int gd = DETECT, gm;
    initgraph(&gd, &gm, NULL);
    drawgrid();
    bresenham_line(2, 2, -40, -20, 0);
    delay(5000);
    closegraph();
    return 0;
}