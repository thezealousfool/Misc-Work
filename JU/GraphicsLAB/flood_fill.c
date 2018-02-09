#include <graphics.h>
#include <math.h>

#define SCRW    640
#define SCRH    480

#define STEPS   10

#define relx(x) (((x) + MAXX) * STEPS)
#define rely(y) ((MAXY - (y)) * STEPS)

#define MAXX    ((int)(floor(SCRW/(STEPS*1.0)) / 2))
#define MAXY    ((int)(floor(SCRH/(STEPS*1.0)) / 2))

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

void init_check_point(int** check_plot) {
    for (int i = 0; i < 2*MAXX; ++i) {
        for (int j = 0; j < 2*MAXY; ++j) {
            check_plot[i][j] = 0;
        }
    }
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

int point_plotted(int **check_plot, int x, int y) {
    return check_plot[x + MAXX][y + MAXY];
}

void mark_plotted(int **check_plot, int x, int y) {
    check_plot[x + MAXX][y + MAXY] = 1;
}

void fill_right(int **check_plot, int x, int y) {
    if (point_plotted(check_plot, x, y))
        return;
    mark_plotted(check_plot, x, y);
    plotpoint(x, y);
    fill_right(check_plot, x+1, y);
    fill_right(check_plot, x, y-1);
    fill_right(check_plot, x, y+1);
}

void fill_left(int **check_plot, int x, int y) {
    if (point_plotted(check_plot, x, y))
        return;
    mark_plotted(check_plot, x, y);
    plotpoint(x, y);
    fill_left(check_plot, x-1, y);
    fill_left(check_plot, x, y-1);
    fill_left(check_plot, x, y+1);
}

int main() {
    int gd = DETECT, gm;
    initgraph(&gd, &gm, NULL);
    drawgrid();
    int seed_x = 0, seed_y = 0;
    int check_plot[2*MAXX][2*MAXY];
    init_check_point(check_plot);
    int points[][2] = {{-8,-4}, {8,-4}, {14,3}, {0,20}, {-14, 3}, {-8, -4}};
    for (int i = 0; i < 6; ++i) {
        bresenham_line(points[i][0], points[i][1], points[i+1][0], points[i+1][1], 0);
    }
    fill_right(check_plot, seed_x, seed_y);
    fill_left(check_plot, seed_x, seed_y);
    delay(5000);
    closegraph();
    return 0;
}