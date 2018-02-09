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
#define	min(x,y)	((x) < (y) ? (x) : (y))

#define VERTICES 5

struct point {
	double x, y;
};

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

void dda(int x1, int y1, int x2, int y2) {
	int dx = x2 - x1;
	int dy = y2 - y1;
	int steps = max(abs(dx), abs(dy));
	float xinc = dx / (float)steps;
	float yinc = dy / (float)steps;

	float x = x1, y = y1;
	for (int i = 0; i < steps; ++i) {
		plotpoint((int)x, (int)y);
		x += xinc; y += yinc;
	}
}

void clip(int x1, int y1, int x2, int y2, int *vertices)
{
	double upper = 1.0, lower = 0.0, dot1, dot2;
	int i;
	struct point boundarypoint1, boundarypoint2, normal, vector, direction;
	direction.x = x2 - x1; direction.y = y2 - y1;
	for(i = 0; i < VERTICES; ++i) {
	  boundarypoint1.x = vertices[2*(i-1)];
	  boundarypoint1.y = vertices[2*(i-1) + 1];
	  boundarypoint2.x = vertices[(2*i) % (2*VERTICES)];
	  boundarypoint2.y = vertices[(2*i + 1) % (2*VERTICES)];
	  normal.x = (int)(boundarypoint1.y - boundarypoint2.y);
	  normal.y = (int)(boundarypoint2.x - boundarypoint1.x);
	  vector.x = (int)(-boundarypoint1.x + x1);
	  vector.y = (int)(-boundarypoint1.y + y1);
	  dot1 = normal.x * direction.x + normal.y * direction.y;
	  dot2 = vector.x * normal.x + vector.y * normal.y;
	  if(dot1 > 0)
	    lower = max(lower, -dot2 / dot1);
	  else if(dot1 < 0)
	    upper = min(upper, -dot2 / dot1);
	  else if(dot2 < 0)
	    return;
	}
	if(lower <= upper) {
	  boundarypoint1.x = (int)(x1 + lower * direction.x);
	  boundarypoint1.y = (int)(y1 + lower * direction.y);
	  boundarypoint2.x = (int)(x1 + upper * direction.x);
	  boundarypoint2.y = (int)(y1 + upper * direction.y);
	  dda(boundarypoint1.x, boundarypoint1.y, boundarypoint2.x, boundarypoint2.y);
	}
	return;
}

void draw_window(int *vertices) {
	int i;
	for (i = 1; i < VERTICES; ++i) {
		dda(vertices[2*(i-1)], vertices[2*(i-1)+1], vertices[2*i], vertices[2*i+1]);
	}
	dda(vertices[2*(i-1)], vertices[2*(i-1)+1], vertices[0], vertices[1]);
}

int main() {
	int gd = DETECT, gm;
	initgraph(&gd, &gm, NULL);
	int vertices[2*VERTICES] = {25,0, 10,20, -20,10, -20,-10, 10,-20};
	drawgrid();
	setcolor(LIGHTGREEN);
	draw_window(vertices);
	setcolor(RED);
	clip(0,20, 30,2, vertices);
	delay(5000);
	closegraph();
	return 0;
}