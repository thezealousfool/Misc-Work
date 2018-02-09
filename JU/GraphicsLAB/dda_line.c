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

int main() {
	int gd = DETECT, gm;
	initgraph(&gd, &gm, NULL);
	drawgrid();
	dda(2, 2, -40, -20);
	delay(5000);
	closegraph();
	return 0;
}