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

#define VERTICES 5

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

void CohenSutherlandLineClipAndDraw(double x0, double y0, double x1, double y1)
{
  int accept = 0;
  OutCode outcode0 = ComputeOutCode(x0, y0);
  OutCode outcode1 = ComputeOutCode(x1, y1);

  while (1) {
    if (!(outcode0 | outcode1)) { // Bitwise OR is 0. Trivially accept and get out of loop
      accept = 1;
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

void PolygonClip(int vertices[2*VERTICES]) {
  int i;
  for (i = 1; i < VERTICES; ++i) {
    CohenSutherlandLineClipAndDraw(vertices[2*(i-1)], vertices[2*(i-1)+1], vertices[2*i], vertices[2*i+1]);
  }
  CohenSutherlandLineClipAndDraw(vertices[2*(i-1)], vertices[2*(i-1)+1], vertices[0], vertices[1]);
  bresenham_line(xmin-1, ymax+1, xmax+1, ymax+1, 0);
  bresenham_line(xmin-1, ymin-1, xmax+1, ymin-1, 0);
  bresenham_line(xmin-1, ymin-1, xmin-1, ymax+1, 0);
  bresenham_line(xmax+1, ymin-1, xmax+1, ymax+1, 0);
}

void drawPoly(int vertices[2*VERTICES]) {
  int i;
  for (i = 1; i < VERTICES; ++i) {
    bresenham_line(vertices[2*(i-1)], vertices[2*(i-1)+1], vertices[2*i], vertices[2*i+1], 0);
  }
  bresenham_line(vertices[2*(i-1)], vertices[2*(i-1)+1], vertices[0], vertices[1], 0);
}

int main() {
    int gd = DETECT, gm;
    initgraph(&gd, &gm, NULL);
    setbkcolor(WHITE);
    setcolor(BLACK);
    drawgrid();
    int vertices[2*VERTICES] = { -10, -10, 5, 2, 20, 5, 2, 15, -10, 10 };
    PolygonClip(vertices);
    delay(5000);
    closegraph();
    return 0;
}
