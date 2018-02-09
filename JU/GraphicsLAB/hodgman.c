#include <stdio.h>
#include <graphics.h>
#include <math.h>
#include <time.h>

#define MAX_POINTS 20

#define	SCRW	640
#define	SCRH	480

#define	STEPS	10

#define	relx(x)	(((x) + MAXX) * STEPS)
#define rely(y) ((MAXY - (y)) * STEPS)

#define	MAXX	(floor(SCRW/(STEPS*1.0)) / 2)
#define	MAXY	(floor(SCRH/(STEPS*1.0)) / 2)

#define	max(x,y)	((x) > (y) ? (x) : (y))

#define sign(val) ((val) < 0) ? -1 : (val) ? 1 : 0

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

void drawline(int x1, int y1, int x2, int y2) {
    int i, interchange = 0, x, y, dx, dy, error, temp, s1, s2;
    x = x1; y = y1;
    dx = abs(x2 - x1); dy = abs(y2 - y1);
    s1 = sign(x2 - x1); s2 = sign(y2 - y1);
    if (dy > dx) {
        temp = dx; dx = dy; dy = temp;
        interchange = 1;
    }
    error = (dy << 1) - dx;
    for (i = 1; i <= dx; ++i) {
        plotpoint(x, y);
        while (error > 0) {
            if (interchange)
                x += s1;
            else
                y += s2;
            error -= dx << 1;
        }
        if (interchange)
            y += s2;
        else
            x += s1;
        error += dy << 1;
    }
}

int xintersect(int x1, int y1, int x2, int y2,
                int x3, int y3, int x4, int y4) {
    int num = (x1*y2 - y1*x2) * (x3-x4) -
              (x1-x2) * (x3*y4 - y3*x4);
    int den = (x1-x2) * (y3-y4) - (y1-y2) * (x3-x4);
    return num/den;
}

int yintersect(int x1, int y1, int x2, int y2,
                int x3, int y3, int x4, int y4) {
    int num = (x1*y2 - y1*x2) * (y3-y4) -
              (y1-y2) * (x3*y4 - y3*x4);
    int den = (x1-x2) * (y3-y4) - (y1-y2) * (x3-x4);
    return num/den;
}

int clip(int poly_points[][2], int poly_size, int x1, int y1, int x2, int y2) {
    int new_points[MAX_POINTS][2], new_poly_size = 0;

    for (int i = 0; i < poly_size; i++) {
        int k = (i+1) % poly_size;
        int ix = poly_points[i][0], iy = poly_points[i][1];
        int kx = poly_points[k][0], ky = poly_points[k][1];
        int i_pos = (x2-x1) * (iy-y1) - (y2-y1) * (ix-x1);
        int k_pos = (x2-x1) * (ky-y1) - (y2-y1) * (kx-x1);
        if (i_pos < 0  && k_pos < 0) {
            new_points[new_poly_size][0] = kx;
            new_points[new_poly_size][1] = ky;
            new_poly_size++;
        } else if (i_pos >= 0  && k_pos < 0) {
            new_points[new_poly_size][0] = xintersect(x1,
                              y1, x2, y2, ix, iy, kx, ky);
            new_points[new_poly_size][1] = yintersect(x1,
                              y1, x2, y2, ix, iy, kx, ky);
            new_poly_size++;
            new_points[new_poly_size][0] = kx;
            new_points[new_poly_size][1] = ky;
            new_poly_size++;
        } else if (i_pos < 0  && k_pos >= 0) {
            new_points[new_poly_size][0] = xintersect(x1,
                              y1, x2, y2, ix, iy, kx, ky);
            new_points[new_poly_size][1] = yintersect(x1,
                              y1, x2, y2, ix, iy, kx, ky);
            new_poly_size++;
        }
    }
    poly_size = new_poly_size;
    for (int i = 0; i < poly_size; i++)
    {
        poly_points[i][0] = new_points[i][0];
        poly_points[i][1] = new_points[i][1];
    }
    return poly_size;
}

void suthHodgClip(int poly_points[][2], int poly_size, int clipper_points[][2], int clipper_size) {
    for (int i=0; i<clipper_size; i++) {
        int k = (i+1) % clipper_size;
        poly_size = clip(poly_points, poly_size, clipper_points[i][0],
             clipper_points[i][1], clipper_points[k][0],
             clipper_points[k][1]);
    }
}

int main() {
    float x,y,dx,dy, d1,d2;
    int gm, gd = DETECT;
    int x1,y1,x2,y2,i,length, delx, dely;
    int a, b, r;
    int novp, novc;
    int gdriver = DETECT, gmode;
    int poly_points[MAX_POINTS][2];
    int clipper_points[MAX_POINTS][2];
    printf("No of vertices of polygon: ");
    scanf ("%d",&novp);
    printf ("Coordinates of vertices: \n");
    for (i = 0; i < novp; ++i) {
        scanf ("%d %d",&poly_points[i][0], &poly_points[i][1]);
    }
    printf("No of vertices of clipping window: ");
    scanf ("%d",&novp);
    printf ("Coordinates of vertices: \n");
    for (i = 0; i < novp; ++i) {
        scanf ("%d %d",&clipper_points[i][0], &clipper_points[i][1]);
    }
    initgraph(&gd, &gm, NULL);
    setbkcolor(WHITE);
    setcolor(BLACK);
    drawgrid();
    for (i = 0; i < novp; ++i) {
        dda(poly_points[i][0], poly_points[i][1], poly_points[(i+1)%novp][0], poly_points[(i+1)%novp][1]);
    }
    for (i=0; i<novc; i++) {
        dda(clipper_points[i][0], clipper_points[i][1] , clipper_points[(i+1)%novp][0], clipper_points[(i+1)%novp][1]);
    }
    delay(3000);
    closegraph();
    suthHodgClip(poly_points, novp, clipper_points, novc);
    initgraph(&gd, &gm, NULL);
    setbkcolor(WHITE);
    setcolor(BLACK);
    drawgrid();
    for (i=0; i<novp; i++) {
      dda(poly_points[i][0], poly_points[i][1] , poly_points[(i+1)%novp][0], poly_points[(i+1)%novp][1]);
    }
    delay(2000);
    closegraph();
    return 0;
}
