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

void matmul_transform(int a[3], float scale[3][3], int b_new[3]) {
	int i, j;
	float b[3] = {0.0, 0.0, 0.0};
	for (i = 0; i < 3; ++i)
		b_new[i] = 0;
	for (i = 0; i < 3; ++i) {
		for (j = 0; j < 3; ++j) {
			// printf("Adding %3.2f to %3.2f\n", a[i] * scale[j][i], b[i]);
			b[i] += a[j] * scale[j][i];
		}
	}
	for (i = 0; i < 3; ++i)
		b_new[i] = (int)(b[i]);
}

void print_scale(float scale[3][3]) {
	int i, j;
	for (i = 0; i < 3; ++i) {
		for (j = 0; j < 3; ++j)
			printf("%1.2f  ", scale[i][j]);
		printf("\n");
	}
	delay(5000);
}

void print_res(int b[3]) {
	int i;
	for (i = 0; i < 3; ++i) {
		printf("%d  ", b[i]);
	}
	printf("\n\n");
}

void scaleline(int x1, int y1, int x2, int y2, float scale_factor, int new_coordinates[4]) {
	int a[3] = {x1, y1, 1};
	float scale[3][3];
	int i, j;
	int b[3], new_x1, new_y1, new_x2, new_y2;
	for (i = 0; i < 3; ++i) {
		for (j = 0; j < 3; ++j) {
			scale[i][j] = 0;
		}
	}
	scale[0][0] = scale_factor;
	scale[1][1] = scale_factor;
	scale[2][2] = 1;
	matmul_transform(a, scale, b);
	new_x1 = (int)(b[0] / b[2] * 1.0);
	new_y1 = (int)(b[1] / b[2] * 1.0);
	a[0] = x2;
	a[1] = y2;
	a[2] = 1;
	matmul_transform(a, scale, b);
	new_x2 = b[0] / b[2];
	new_y2 = b[1] / b[2];
	new_coordinates[0] = new_x1;
	new_coordinates[1] = new_y1;
	new_coordinates[2] = new_x2;
	new_coordinates[3] = new_y2;
}

void translateline(int x1, int y1, int x2, int y2, int new_org_x, int new_org_y, int new_coordinates[4]) {
	int a[3] = {x1, y1, 1};
	float scale[3][3];
	int i, j;
	int b[3], new_x1, new_y1, new_x2, new_y2;
	for (i = 0; i < 3; ++i) {
		for (j = 0; j < 3; ++j) {
			scale[i][j] = 0;
		}
	}
	scale[0][0] = 1;
	scale[1][1] = 1;
	scale[2][0] = new_org_x;
	scale[2][1] = new_org_y;
	scale[2][2] = 1;
	matmul_transform(a, scale, b);
	new_x1 = (int)(b[0] / b[2] * 1.0);
	new_y1 = (int)(b[1] / b[2] * 1.0);
	a[0] = x2;
	a[1] = y2;
	a[2] = 1;
	matmul_transform(a, scale, b);
	new_x2 = b[0] / b[2];
	new_y2 = b[1] / b[2];
	new_coordinates[0] = new_x1;
	new_coordinates[1] = new_y1;
	new_coordinates[2] = new_x2;
	new_coordinates[3] = new_y2;
}

void rotateline(int x1, int y1, int x2, int y2, int deg, int new_coordinates[4]) {
	int a[3] = {x1, y1, 1};
	float scale[3][3];
	int i, j;
	int b[3], new_x1, new_y1, new_x2, new_y2;
	float cos_theta = cos(deg * 3.1415926 / 180.0);
	float sin_theta = sin(deg * 3.1415926 / 180.0);
	for (i = 0; i < 3; ++i) {
		for (j = 0; j < 3; ++j) {
			scale[i][j] = 0;
		}
	}
	scale[0][0] = cos_theta;
	scale[0][1] = sin_theta;
	scale[1][0] = -sin_theta;
	scale[1][1] = cos_theta;
	scale[2][2] = 1;
	matmul_transform(a, scale, b);
	new_x1 = (int)(b[0] / b[2] * 1.0);
	new_y1 = (int)(b[1] / b[2] * 1.0);
	a[0] = x2;
	a[1] = y2;
	a[2] = 1;
	matmul_transform(a, scale, b);
	new_x2 = b[0] / b[2];
	new_y2 = b[1] / b[2];
	new_coordinates[0] = new_x1;
	new_coordinates[1] = new_y1;
	new_coordinates[2] = new_x2;
	new_coordinates[3] = new_y2;
}

void shearline(int x1, int y1, int x2, int y2, float shear_x, float shear_y, int new_coordinates[4]) {
	int a[3] = {x1, y1, 1};
	float scale[3][3];
	int i, j;
	int b[3], new_x1, new_y1, new_x2, new_y2;
	for (i = 0; i < 3; ++i) {
		for (j = 0; j < 3; ++j) {
			scale[i][j] = 0;
		}
	}
	scale[0][1] = shear_x;
	scale[1][0] = shear_y;
	scale[0][0] = 1;
	scale[1][1] = 1;
	scale[2][2] = 1;
	matmul_transform(a, scale, b);
	new_x1 = (int)(b[0] / b[2] * 1.0);
	new_y1 = (int)(b[1] / b[2] * 1.0);
	a[0] = x2;
	a[1] = y2;
	a[2] = 1;
	matmul_transform(a, scale, b);
	new_x2 = b[0] / b[2];
	new_y2 = b[1] / b[2];
	new_coordinates[0] = new_x1;
	new_coordinates[1] = new_y1;
	new_coordinates[2] = new_x2;
	new_coordinates[3] = new_y2;
}

void draw_tri(int x1, int y1, int x2, int y2, int x3, int y3) {
	dda(x1,y1,x2,y2);
	dda(x2,y2,x3,y3);
	dda(x3,y3,x1,y1);
}

void scale_tri(int x1, int y1, int x2, int y2, int x3, int y3, float scale_factor, int new_coordinates[3][4]) {
	scaleline(x1,y1,x2,y2, scale_factor, new_coordinates[0]);
	scaleline(x2,y2,x3,y3, scale_factor, new_coordinates[1]);
	scaleline(x3,y3,x1,y1, scale_factor, new_coordinates[2]);
}

void trans_tri(int x1, int y1, int x2, int y2, int x3, int y3, int new_org_x, int new_org_y, int new_coordinates[3][4]) {
	translateline(x1,y1,x2,y2, new_org_x,new_org_y, new_coordinates[0]);
	translateline(x2,y2,x3,y3, new_org_x,new_org_y, new_coordinates[1]);
	translateline(x3,y3,x1,y1, new_org_x,new_org_y, new_coordinates[2]);
}

void rotate_tri(int x1, int y1, int x2, int y2, int x3, int y3, int deg, int new_coordinates[3][4]) {
	rotateline(x1,y1,x2,y2, deg, new_coordinates[0]);
	rotateline(x2,y2,x3,y3, deg, new_coordinates[1]);
	rotateline(x3,y3,x1,y1, deg, new_coordinates[2]);
}

void shear_tri(int x1, int y1, int x2, int y2, int x3, int y3, float shear_x, float shear_y, int new_coordinates[3][4]) {
	shearline(x1,y1,x2,y2, shear_x, shear_y, new_coordinates[0]);
	shearline(x2,y2,x3,y3, shear_x, shear_y, new_coordinates[1]);
	shearline(x3,y3,x1,y1, shear_x, shear_y, new_coordinates[2]);
}

void reflect_tri(int x1, int y1, int x2, int y2, int x3, int y3, float slope, float yintercept, int new_coordinates[3][4]) {
	new_coordinates[0][0] = x1;
	new_coordinates[0][1] = y1;
	new_coordinates[0][2] = x2;
	new_coordinates[0][3] = y2;
	new_coordinates[1][0] = x2;
	new_coordinates[1][1] = y2;
	new_coordinates[1][2] = x3;
	new_coordinates[1][3] = y3;
	new_coordinates[2][0] = x3;
	new_coordinates[2][1] = y3;
	new_coordinates[2][2] = x1;
	new_coordinates[2][3] = y1;
	trans_tri(new_coordinates[0][0], new_coordinates[0][1], new_coordinates[1][0], new_coordinates[1][1], new_coordinates[2][0], new_coordinates[2][1], 0, (-1 * (int)(yintercept)), new_coordinates);
	rotate_tri(new_coordinates[0][0], new_coordinates[0][1], new_coordinates[1][0], new_coordinates[1][1], new_coordinates[2][0], new_coordinates[2][1], atan(slope) * -180 / 3.1415926, new_coordinates);
	new_coordinates[0][1] *= -1;
	new_coordinates[0][3] *= -1;
	new_coordinates[1][1] *= -1;
	new_coordinates[1][3] *= -1;
	new_coordinates[2][1] *= -1;
	new_coordinates[2][3] *= -1;
	rotate_tri(new_coordinates[0][0], new_coordinates[0][1], new_coordinates[1][0], new_coordinates[1][1], new_coordinates[2][0], new_coordinates[2][1], atan(slope) * 180 / 3.1415926, new_coordinates);
	trans_tri(new_coordinates[0][0], new_coordinates[0][1], new_coordinates[1][0], new_coordinates[1][1], new_coordinates[2][0], new_coordinates[2][1], 0, (int)(yintercept), new_coordinates);
}

int main() {
	int gd = DETECT, gm;
	int x1, y1, x2, y2, x3, y3, choice, loop;
	int triCoordinates[3][4];
	float input1, input2, input3;
	printf("Enter x and y of vertices of triangle:\n");
	scanf("%d", &x1);
	scanf("%d", &y1);
	scanf("%d", &x2);
	scanf("%d", &y2);
	scanf("%d", &x3);
	scanf("%d", &y3);
	initgraph(&gd, &gm, NULL);
	setbkcolor(WHITE);
  setcolor(BLACK);
	drawgrid();
	draw_tri(x1, y1, x2, y2, x3, y3);
	delay(2000);
	closegraph();
	printf("1. Scaling\n2. Translation\n3. Rotation\n4. Shearing\n5. Reflection\n6. Composite\nEnter choice: ");
	scanf("%d", &choice);
	switch (choice) {
		case 1: {
			printf("Scaling factor: ");
			scanf("%f", &input1);
			initgraph(&gd, &gm, NULL);
			setbkcolor(WHITE);
		  setcolor(BLACK);
			drawgrid();
			scale_tri(x1, y1, x2, y2, x3, y3, input1, triCoordinates);
			draw_tri(triCoordinates[0][0], triCoordinates[0][1], triCoordinates[1][0], triCoordinates[1][1], triCoordinates[2][0], triCoordinates[2][1]);
			delay(2000);
			closegraph();
			break;
		}
		case 2: {
			printf("New x and y of origin: ");
			scanf("%f %f", &input1, &input2);
			initgraph(&gd, &gm, NULL);
			setbkcolor(WHITE);
		  setcolor(BLACK);
			drawgrid();
			trans_tri(x1, y1, x2, y2, x3, y3, (int)input1, (int)input2, triCoordinates);
			draw_tri(triCoordinates[0][0], triCoordinates[0][1], triCoordinates[1][0], triCoordinates[1][1], triCoordinates[2][0], triCoordinates[2][1]);
			delay(2000);
			closegraph();
			break;
		}
		case 3: {
			printf("Angle of rotation: ");
			scanf("%f", &input1);
			initgraph(&gd, &gm, NULL);
			setbkcolor(WHITE);
		  setcolor(BLACK);
			drawgrid();
			rotate_tri(x1, y1, x2, y2, x3, y3, (int)input1, triCoordinates);
			draw_tri(triCoordinates[0][0], triCoordinates[0][1], triCoordinates[1][0], triCoordinates[1][1], triCoordinates[2][0], triCoordinates[2][1]);
			delay(2000);
			closegraph();
			break;
		}
		case 4: {
			printf("Shearing vectors for x and y: ");
			scanf("%f %f", &input1, &input2);
			initgraph(&gd, &gm, NULL);
			setbkcolor(WHITE);
		  setcolor(BLACK);
			drawgrid();
			shear_tri(x1, y1, x2, y2, x3, y3, input1, input2, triCoordinates);
			draw_tri(triCoordinates[0][0], triCoordinates[0][1], triCoordinates[1][0], triCoordinates[1][1], triCoordinates[2][0], triCoordinates[2][1]);
			delay(2000);
			closegraph();
			break;
		}
		case 5: {
			printf("Slope and Y-intercept: ");
			scanf("%f %f", &input1, &input2);
			initgraph(&gd, &gm, NULL);
			setbkcolor(WHITE);
		  setcolor(BLACK);
			drawgrid();
			reflect_tri(x1, y1, x2, y2, x3, y3, input1, input2, triCoordinates);
			draw_tri(triCoordinates[0][0], triCoordinates[0][1], triCoordinates[1][0], triCoordinates[1][1], triCoordinates[2][0], triCoordinates[2][1]);
			delay(2000);
			closegraph();
			break;
		}
		case 6: {
			printf("Enter no of operations: ");
			scanf("%f", &input3);
			printf("1. Scaling\n2. Translation\n3. Rotation\n4. Shearing\n5. Reflection");
			for (loop = 0; loop < (int)input3; ++loop) {
				printf("Operation %d Choice: ", loop+1);
				scanf("%d", &choice);
				triCoordinates[0][0] = x1;
				triCoordinates[0][1] = y1;
				triCoordinates[0][2] = x2;
				triCoordinates[0][3] = y2;
				triCoordinates[1][0] = x2;
				triCoordinates[1][1] = y2;
				triCoordinates[1][2] = x3;
				triCoordinates[1][3] = y3;
				triCoordinates[2][0] = x3;
				triCoordinates[2][1] = y3;
				triCoordinates[2][2] = x1;
				triCoordinates[2][3] = y1;
				switch(choice) {
					case 1: {
						printf("Scaling factor: ");
						scanf("%f", &input1);
						scale_tri(triCoordinates[0][0], triCoordinates[0][1], triCoordinates[1][0], triCoordinates[1][1], triCoordinates[2][0], triCoordinates[2][1], input1, triCoordinates);
						break;
					}
					case 2: {
						printf("New x and y of origin: ");
						scanf("%f %f", &input1, &input2);
						trans_tri(triCoordinates[0][0], triCoordinates[0][1], triCoordinates[1][0], triCoordinates[1][1], triCoordinates[2][0], triCoordinates[2][1], (int)input1, (int)input2, triCoordinates);
						break;
					}
					case 3: {
						printf("Angle of rotation: ");
						scanf("%f", &input1);
						rotate_tri(triCoordinates[0][0], triCoordinates[0][1], triCoordinates[1][0], triCoordinates[1][1], triCoordinates[2][0], triCoordinates[2][1], (int)input1, triCoordinates);
						break;
					}
					case 4: {
						printf("Shearing vectors for x and y: ");
						scanf("%f %f", &input1, &input2);
						shear_tri(triCoordinates[0][0], triCoordinates[0][1], triCoordinates[1][0], triCoordinates[1][1], triCoordinates[2][0], triCoordinates[2][1], input1, input2, triCoordinates);
						break;
					}
					case 5: {
						printf("Slope and Y-intercept: ");
						scanf("%f %f", &input1, &input2);
						reflect_tri(triCoordinates[0][0], triCoordinates[0][1], triCoordinates[1][0], triCoordinates[1][1], triCoordinates[2][0], triCoordinates[2][1], input1, input2, triCoordinates);
						break;
					}
					default: {
						printf("Wrong entry!!\n");
						--loop;
					}
				}
			}
			initgraph(&gd, &gm, NULL);
			setbkcolor(WHITE);
		  setcolor(BLACK);
			drawgrid();
			draw_tri(triCoordinates[0][0], triCoordinates[0][1], triCoordinates[1][0], triCoordinates[1][1], triCoordinates[2][0], triCoordinates[2][1]);
			delay(2000);
			closegraph();
			break;
		}
		default: printf("Wrong Entry!!\n");
	}
	return 0;
}
