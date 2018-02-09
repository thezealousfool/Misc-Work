#include <graphics.h>
#include <math.h>

#define	SCRW	640
#define	SCRH	480

#define	STEPS	10

#define	relx(x)	(((x) + MAXX) * STEPS)
#define rely(y) ((MAXY - (y)) * STEPS)

#define	MAXX	(floor(SCRW/(STEPS*1.0)) / 2)
#define	MAXY	(floor(SCRH/(STEPS*1.0)) / 2)

#define	max(x,y)	((x) > (y) ? (x) : (y))

#define relmidx(x) \
  (abs((((x) + MAXX) * STEPS) + (STEPS / 2)) > SCRW || \
  ((((x) + MAXX) * STEPS) + (STEPS / 2)) < 0) \
  ? -SCRW-1 : ((((x) + MAXX) * STEPS) + (STEPS / 2))

#define relmidy(y) \
  (abs(((MAXY - (y)) * STEPS) - (STEPS / 2)) > SCRH || \
  (((MAXY - (y)) * STEPS) - (STEPS / 2)) < 0) \
  ? -SCRH-1 : (((MAXY - (y)) * STEPS) - (STEPS / 2))

#define _getpixelcolor(x, y) \
  ((relmidx(x) >= 0) && (relmidy(y) >= 0)) \
  ? getpixel(relmidx(x), relmidy(y)) : -1

#define getpixelcolor(p) _getpixelcolor((p).x, (p).y)
#define plotpoint(p) _plotpoint((p).x, (p).y)

typedef struct {
  int x, y;
} point;

void drawgrid() {
  for (int i = 0; STEPS * i <= SCRW; ++i) {
  line(STEPS * i, 0, STEPS * i, SCRH);
  }
  for (int i = 0; STEPS * i <= SCRH; ++i) {
  line(0, STEPS * i, SCRW, STEPS * i);
  }
}

void _plotpoint(int x, int y) {
  if (abs(x) >= MAXX || abs(y) >= MAXY)
  return;
  int arr[10] = {relx(x), rely(y),
   relx(x+1), rely(y),
   relx(x+1), rely(y+1),
   relx(x), rely(y+1),
   relx(x), rely(y)};
  fillpoly(5, arr);
}

void dda(point p1, point p2) {
  int x1 = p1.x, y1 = p1.y;
  int x2 = p2.x, y2 = p2.y;
  int dx = x2 - x1, dy = y2 - y1;
  int steps = max(abs(dx), abs(dy));
  float xinc = dx / (float)steps;
  float yinc = dy / (float)steps;
  float x = x1, y = y1;
  for (int i = 0; i < steps; ++i) {
  _plotpoint((int)x, (int)y);
  x += xinc; y += yinc;
  }
}

void fillright(point p) {
  int currentcolor = WHITE;
  point nextpoint;
  currentcolor = getpixelcolor(p);
  if (currentcolor == -1)
  return;
  if (currentcolor == WHITE || currentcolor == BLACK) {
  plotpoint(p);
  nextpoint.x = (p.x)+1; nextpoint.y = p.y;
  fillright(nextpoint);
  nextpoint.x = p.x; nextpoint.y = (p.y)-1;
  fillright(nextpoint);
  nextpoint.x = p.x; nextpoint.y = (p.y)+1;
  fillright(nextpoint);
  }
}

void fillleft(point p) {
  int currentcolor = WHITE;
  point nextpoint;
  currentcolor = getpixelcolor(p);
  if (currentcolor == -1)
  return;
  if (currentcolor == WHITE || currentcolor == BLACK) {
  plotpoint(p);
  nextpoint.x = (p.x)-1; nextpoint.y = p.y;
  fillleft(nextpoint);
  nextpoint.x = p.x; nextpoint.y = (p.y)-1;
  fillleft(nextpoint);
  nextpoint.x = p.x; nextpoint.y = (p.y)+1;
  fillleft(nextpoint);
  }
}

void polyfill(point p) {
  fillright(p);
  p.x--;
  fillleft(p);
}

int main() {
  int gd = DETECT, gm;
  int novertices;
  point vertices[11];
  point seedpoint;
  int i;
  printf("No of Vetices: ");
  scanf("%d", &novertices);
  printf("Co-ordinates of vertices:\n");
  for (i = 0; i < novertices; ++i) {
  scanf("%d %d", &(vertices[i].x), &(vertices[i].y));
  }
  vertices[i].x = vertices[0].x;
  vertices[i].y = vertices[0].y;
  printf("Co-ordinates of seed: ");
  scanf("%d %d", &(seedpoint.x), &(seedpoint.y));
  initgraph(&gd, &gm, NULL);
  setbkcolor(WHITE);
  setcolor(BLACK);
  drawgrid();
  setcolor(BLUE);
  for (i = 0; i < novertices; ++i) {
  dda(vertices[i], vertices[i+1]);
  }
  setcolor(RED);
  polyfill(seedpoint);
  delay(5000);
  closegraph();
  return 0;
}
