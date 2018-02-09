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

#define xmin -MAXX/2
#define ymin -MAXY/2
#define xmax MAXX/2
#define ymax MAXY/2

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

typedef int OutCode;

const int INSIDE = 0; // 0000
const int LEFT = 1;   // 0001
const int RIGHT = 2;  // 0010
const int BOTTOM = 4; // 0100
const int TOP = 8;    // 1000

OutCode ComputeOutCode(double x, double y)
{
	OutCode code;

	code = INSIDE;

	if (x < xmin)           // to the left of clip window
		code |= LEFT;
	else if (x > xmax)      // to the right of clip window
		code |= RIGHT;
	if (y < ymin)           // below the clip window
		code |= BOTTOM;
	else if (y > ymax)      // above the clip window
		code |= TOP;

	return code;
}

// Cohen–Sutherland clipping algorithm clips a line from
// P0 = (x0, y0) to P1 = (x1, y1) against a rectangle with
// diagonal from (xmin, ymin) to (xmax, ymax).
void CohenSutherlandLineClipAndDraw(double x0, double y0, double x1, double y1)
{
	// compute outcodes for P0, P1, and whatever point lies outside the clip rectangle
	OutCode outcode0 = ComputeOutCode(x0, y0);
	OutCode outcode1 = ComputeOutCode(x1, y1);
	bool accept = false;

	while (true) {
		if (!(outcode0 | outcode1)) { // Bitwise OR is 0. Trivially accept and get out of loop
			accept = true;
			break;
		} else if (outcode0 & outcode1) { // Bitwise AND is not 0. (implies both end points are in the same region outside the window). Reject and get out of loop
			break;
		} else {
			double x, y;

			OutCode outcodeOut = outcode0 ? outcode0 : outcode1;

			if (outcodeOut & TOP) {           // point is above the clip rectangle
				x = x0 + (x1 - x0) * (ymax - y0) / (y1 - y0);
				y = ymax;
			} else if (outcodeOut & BOTTOM) { // point is below the clip rectangle
				x = x0 + (x1 - x0) * (ymin - y0) / (y1 - y0);
				y = ymin;
			} else if (outcodeOut & RIGHT) {  // point is to the right of clip rectangle
				y = y0 + (y1 - y0) * (xmax - x0) / (x1 - x0);
				x = xmax;
			} else if (outcodeOut & LEFT) {   // point is to the left of clip rectangle
				y = y0 + (y1 - y0) * (xmin - x0) / (x1 - x0);
				x = xmin;
			}

			if (outcodeOut == outcode0) {
				x0 = x;
				y0 = y;
				outcode0 = ComputeOutCode(x0, y0);
			} else {
				x1 = x;
				y1 = y;
				outcode1 = ComputeOutCode(x1, y1);
			}
		}
	}
	if (accept) {
		bresenham_line((int)x0, (int)y0, (int)x1, (int)y1, 0);
	}
}

int main() {
    int gd = DETECT, gm;
    initgraph(&gd, &gm, NULL);
    drawgrid();
    CohenSutherlandLineClipAndDraw(-500, 500, 500, -500);
    delay(5000);
    closegraph();
    return 0;
}