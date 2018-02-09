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

void matmul_transform(int a[4], float scale[4][4], int b_new[4]) {
	int i, j;
	float b[4] = {0.0, 0.0, 0.0, 0.0};
	for (i = 0; i < 4; ++i)
		b_new[i] = 0;
	for (i = 0; i < 4; ++i) {
		for (j = 0; j < 4; ++j) {
			// printf("Adding %3.2f to %3.2f\n", a[i] * scale[j][i], b[i]);
			b[i] += a[j] * scale[j][i];
		}
	}
	for (i = 0; i < 4; ++i)
		b_new[i] = (int)(b[i]);
}

void print_scale(float scale[4][4]) {
	int i, j;
	for (i = 0; i < 4; ++i) {
		for (j = 0; j < 4; ++j)
			printf("%1.2f  ", scale[i][j]);
		printf("\n");
	}
	delay(5000);
}

void print_res(int b[4]) {
	int i;
	for (i = 0; i < 4; ++i) {
		printf("%d  ", b[i]);
	}
	printf("\n\n");
}

void scaleline(int x1, int y1, int z1, int x2, int y2, int z2, float scale_factor, int new_coordinates[6]) {
	int a[4] = {x1, y1, z1, 1};
	float scale[4][4];
	int i, j;
	int b[4], new_x1, new_y1, new_z1, new_x2, new_y2, new_z2;
	for (i = 0; i < 4; ++i) {
		for (j = 0; j < 4; ++j) {
			scale[i][j] = 0;
		}
	}
	scale[0][0] = scale_factor;
	scale[1][1] = scale_factor;
	scale[2][2] = scale_factor;
	scale[3][3] = 1;
	matmul_transform(a, scale, b);
	new_x1 = (int)(b[0] / b[3] * 1.0);
	new_y1 = (int)(b[1] / b[3] * 1.0);
	new_z1 = (int)(b[2] / b[3] * 1.0);
	a[0] = x2;
	a[1] = y2;
	a[2] = 1;
	matmul_transform(a, scale, b);
	new_x2 = b[0] / b[3];
	new_y2 = b[1] / b[3];
	new_z2 = b[2] / b[3];
	new_coordinates[0] = new_x1;
	new_coordinates[1] = new_y1;
	new_coordinates[2] = new_z1;
	new_coordinates[3] = new_x2;
	new_coordinates[4] = new_y2;
	new_coordinates[5] = new_z2;
}

void translateline(int x1, int y1, int z1, int x2, int y2, int z2, int new_org_x, int new_org_y, int new_org_z, int new_coordinates[6]) {
	int a[4] = {x1, y1, z1, 1};
	float scale[4][4];
	int i, j;
	int b[4], new_x1, new_y1, new_z1, new_x2, new_y2, new_z2;
	for (i = 0; i < 4; ++i) {
		for (j = 0; j < 4; ++j) {
			scale[i][j] = 0;
		}
	}
	scale[0][0] = 1;
	scale[1][1] = 1;
	scale[2][2] = 1;
	scale[3][3] = 1;
	scale[3][0] = new_org_x;
	scale[3][1] = new_org_y;
	scale[3][2] = new_org_z;
	matmul_transform(a, scale, b);
	new_x1 = (int)(b[0] / b[3] * 1.0);
	new_y1 = (int)(b[1] / b[3] * 1.0);
	new_z1 = (int)(b[2] / b[3] * 1.0);
	a[0] = x2;
	a[1] = y2;
	a[2] = z2;
	a[3] = 1;
	matmul_transform(a, scale, b);
	new_x2 = b[0] / b[3];
	new_y2 = b[1] / b[3];
	new_y2 = b[2] / b[3];
	new_coordinates[0] = new_x1;
	new_coordinates[1] = new_y1;
	new_coordinates[2] = new_z1;
	new_coordinates[3] = new_x2;
	new_coordinates[4] = new_y2;
	new_coordinates[5] = new_z2;
}

void rotateline(int x1, int y1, int z1, int x2, int y2, int z2, int deg, int new_coordinates[6]) {
	int a[4] = {x1, y1, z1, 1};
	float scale[4][4];
	int i, j;
	int b[4], new_x1, new_y1, new_z1, new_x2, new_y2, new_z2;
	float cos_theta = cos(deg * 3.1415926 / 180.0);
	float sin_theta = sin(deg * 3.1415926 / 180.0);
	for (i = 0; i < 4; ++i) {
		for (j = 0; j < 4; ++j) {
			scale[i][j] = 0;
		}
	}
	scale[0][0] = cos_theta;
	scale[0][1] = -sin_theta;
	scale[1][0] = sin_theta;
	scale[1][1] = cos_theta;
	scale[2][2] = 1;
	scale[3][3] = 1;
	matmul_transform(a, scale, b);
	new_x1 = (int)(b[0] / b[3] * 1.0);
	new_y1 = (int)(b[1] / b[3] * 1.0);
	new_z1 = (int)(b[2] / b[3] * 1.0);
	a[0] = x2;
	a[1] = y2;
	a[2] = z2;
	a[3] = 1;
	matmul_transform(a, scale, b);
	new_x2 = b[0] / b[3];
	new_y2 = b[1] / b[3];
	new_y2 = b[2] / b[3];
	new_coordinates[0] = new_x1;
	new_coordinates[1] = new_y1;
	new_coordinates[2] = new_z1;
	new_coordinates[3] = new_x2;
	new_coordinates[4] = new_y2;
	new_coordinates[5] = new_z2;
}

void shearline(int x1, int y1, int z1, int x2, int y2, int z2, float shear_x, float shear_y, float shear_z, int new_coordinates[6]) {
	int a[4] = {x1, y1, z1, 1};
	float scale[4][4];
	int i, j;
	int b[4], new_x1, new_y1, new_z1, new_x2, new_y2, new_z2;
	for (i = 0; i < 4; ++i) {
		for (j = 0; j < 4; ++j) {
			scale[i][j] = 0;
		}
	}
	scale[0][1] = shear_x;
	scale[1][0] = shear_y;
	scale[0][0] = 1;
	scale[1][1] = 1;
	scale[2][2] = 1;
	matmul_transform(a, scale, b);
	new_x1 = (int)(b[0] / b[3] * 1.0);
	new_y1 = (int)(b[1] / b[3] * 1.0);
	new_z1 = (int)(b[2] / b[3] * 1.0);
	a[0] = x2;
	a[1] = y2;
	a[2] = z2;
	a[3] = 1;
	matmul_transform(a, scale, b);
	new_x2 = b[0] / b[3];
	new_y2 = b[1] / b[3];
	new_y2 = b[2] / b[3];
	new_coordinates[0] = new_x1;
	new_coordinates[1] = new_y1;
	new_coordinates[2] = new_z1;
	new_coordinates[3] = new_x2;
	new_coordinates[4] = new_y2;
	new_coordinates[5] = new_z2;
}

void draw_pir(int x1, int y1, int z1, int x2, int y2, int z2, int x3, int y3, int z3, int x4, int y4, int z4) {
	dda(x1,y1,x2,y2);
	dda(x2,y2,x3,y3);
	dda(x3,y3,x4,y4);
	dda(x4,y4,x1,y1);
}

void scale_pir(int x1, int y1, int z1, int x2, int y2, int z2, int x3, int y3, int z3, int x4, int y4, int z4, float scale_factor, int new_coordinates[4][6]) {
	scaleline(x1,y1,z1,x2,y2,z2, scale_factor, new_coordinates[0]);
	scaleline(x2,y2,z2,x3,y3,z3, scale_factor, new_coordinates[1]);
	scaleline(x3,y3,z3,x4,y4,z4, scale_factor, new_coordinates[2]);
	scaleline(x4,y4,z4,x1,y1,z1, scale_factor, new_coordinates[3]);
}

void trans_pir(int x1, int y1, int z1, int x2, int y2, int z2, int x3, int y3, int z3, int x4, int y4, int z4, int new_org_x, int new_org_y, int new_org_z, int new_coordinates[4][6]) {
	translateline(x1,y1,z1,x2,y2,z2, new_org_x,new_org_y,new_org_z, new_coordinates[0]);
	translateline(x2,y2,z2,x3,y3,z3, new_org_x,new_org_y,new_org_z, new_coordinates[1]);
	translateline(x3,y3,z3,x4,y4,z4, new_org_x,new_org_y,new_org_z, new_coordinates[2]);
	translateline(x4,y4,z4,x1,y1,z1, new_org_x,new_org_y,new_org_z, new_coordinates[3]);
}

void rotate_pir(int x1, int y1, int z1, int x2, int y2, int z2, int x3, int y3, int z3, int x4, int y4, int z4, int deg, int new_coordinates[4][6]) {
	rotateline(x1,y1,z1,x2,y2,z2, deg, new_coordinates[0]);
	rotateline(x2,y2,z2,x3,y3,z3, deg, new_coordinates[1]);
	rotateline(x3,y3,z3,x4,y4,z4, deg, new_coordinates[2]);
	rotateline(x4,y4,z4,x1,y1,z1, deg, new_coordinates[3]);
}

void shear_pir(int x1, int y1, int z1, int x2, int y2, int z2, int x3, int y3, int z3, int x4, int y4, int z4, float shear_x, float shear_y, float shear_z, int new_coordinates[3][6]) {
	shearline(x1,y1,z1,x2,y2,z2, shear_x, shear_y, shear_z, new_coordinates[0]);
	shearline(x2,y2,z2,x3,y3,z3, shear_x, shear_y, shear_z, new_coordinates[1]);
	shearline(x3,y3,z3,x4,y4,z4, shear_x, shear_y, shear_z, new_coordinates[2]);
	shearline(x4,y4,z4,x1,y1,z1, shear_x, shear_y, shear_z, new_coordinates[3]);
}

int main() {
	int gd = DETECT, gm;
	int x1, y1, z1, x2, y2, z2, x3, y3, z3, x4, y4, z4, choice, loop;
	int triCoordinates[4][6];
	float input1, input2, input3, input4;
	printf("Enter x, y and z of vertices of pyramid:\n");
	scanf("%d", &x1);
	scanf("%d", &y1);
	scanf("%d", &z1);
	scanf("%d", &x2);
	scanf("%d", &y2);
	scanf("%d", &z2);
	scanf("%d", &x3);
	scanf("%d", &y3);
	scanf("%d", &z3);
	scanf("%d", &x4);
	scanf("%d", &y4);
	scanf("%d", &z4);
	initgraph(&gd, &gm, NULL);
	drawgrid();
	draw_pir(x1, y1, z1, x2, y2, z2, x3, y3, z3, x4, y4, z4);
	delay(2000);
	closegraph();
	printf("1. Scaling\n2. Translation\n3. Rotation\n4. Shearing\n5. Composite\nEnter choice: ");
	scanf("%d", &choice);
	switch (choice) {
		case 1: {
			printf("Scaling factor: ");
			scanf("%f", &input1);
			initgraph(&gd, &gm, NULL);
			drawgrid();
			scale_pir(x1, y1, z1, x2, y2, z2, x3, y3, z3, x4, y4, z4, input1, triCoordinates);
			draw_pir(triCoordinates[0][0], triCoordinates[0][1], triCoordinates[0][2], triCoordinates[1][0], triCoordinates[1][1], triCoordinates[1][2], triCoordinates[2][0], triCoordinates[2][1], triCoordinates[2][2], triCoordinates[3][0], triCoordinates[3][1], triCoordinates[3][2]);
			delay(2000);
			closegraph();
			break;
		}
		case 2: {
			printf("New x, y and z of origin: ");
			scanf("%f %f %f", &input1, &input2, &input3);
			initgraph(&gd, &gm, NULL);
			drawgrid();
			trans_pir(x1, y1, z1, x2, y2, z2, x3, y3, z3, x4, y4, z4, (int)input1, (int)input2, (int)input3, triCoordinates);
			draw_pir(triCoordinates[0][0], triCoordinates[0][1], triCoordinates[0][2], triCoordinates[1][0], triCoordinates[1][1], triCoordinates[1][2], triCoordinates[2][0], triCoordinates[2][1], triCoordinates[2][2], triCoordinates[3][0], triCoordinates[3][1], triCoordinates[3][2]);
			delay(2000);
			closegraph();
			break;
		}
		case 3: {
			printf("Angle of rotation: ");
			scanf("%f", &input1);
			initgraph(&gd, &gm, NULL);
			drawgrid();
			rotate_pir(x1, y1, z1, x2, y2, z2, x3, y3, z3, x4, y4, z4, (int)input1, triCoordinates);
			draw_pir(triCoordinates[0][0], triCoordinates[0][1], triCoordinates[0][2], triCoordinates[1][0], triCoordinates[1][1], triCoordinates[1][2], triCoordinates[2][0], triCoordinates[2][1], triCoordinates[2][2], triCoordinates[3][0], triCoordinates[3][1], triCoordinates[3][2]);
			delay(2000);
			closegraph();
			break;
		}
		case 4: {
			printf("Shearing vectors for x, y and z: ");
			scanf("%f %f %f", &input1, &input2, &input3);
			initgraph(&gd, &gm, NULL);
			drawgrid();
			shear_pir(x1, y1, z1, x2, y2, z2, x3, y3, z3, x4, y4, z4, input1, input2, input3, triCoordinates);
			draw_pir(triCoordinates[0][0], triCoordinates[0][1], triCoordinates[0][2], triCoordinates[1][0], triCoordinates[1][1], triCoordinates[1][2], triCoordinates[2][0], triCoordinates[2][1], triCoordinates[2][2], triCoordinates[3][0], triCoordinates[3][1], triCoordinates[3][2]);
			delay(2000);
			closegraph();
			break;
		}
		case 5: {
			printf("Enter no of operations: ");
			scanf("%f", &input3);
			printf("1. Scaling\n2. Translation\n3. Rotation\n4. Shearing\n");
			for (loop = 0; loop < (int)input3; ++loop) {
				printf("Operation %d Choice: ", loop+1);
				scanf("%d", &choice);
				triCoordinates[0][0] = x1;
				triCoordinates[0][1] = y1;
				triCoordinates[0][2] = z1;
				triCoordinates[0][3] = x2;
				triCoordinates[0][4] = y2;
				triCoordinates[0][5] = z2;
				triCoordinates[1][0] = x2;
				triCoordinates[1][1] = y2;
				triCoordinates[1][2] = z2;
				triCoordinates[1][3] = x2;
				triCoordinates[1][4] = y2;
				triCoordinates[1][5] = z2;
				triCoordinates[2][0] = x3;
				triCoordinates[2][1] = y3;
				triCoordinates[2][2] = z3;
				triCoordinates[2][3] = x4;
				triCoordinates[2][4] = y4;
				triCoordinates[2][5] = z4;
				triCoordinates[3][0] = x4;
				triCoordinates[3][1] = y4;
				triCoordinates[3][2] = z4;
				triCoordinates[3][3] = x1;
				triCoordinates[3][4] = y1;
				triCoordinates[3][5] = z1;
				switch(choice) {
					case 1: {
						printf("Scaling factor: ");
						scanf("%f", &input1);
						scale_pir(triCoordinates[0][0], triCoordinates[0][1], triCoordinates[0][2], triCoordinates[1][0], triCoordinates[1][1], triCoordinates[1][2], triCoordinates[2][0], triCoordinates[2][1], triCoordinates[2][2], triCoordinates[3][0], triCoordinates[3][1], triCoordinates[3][2], input1, triCoordinates);
						break;
					}
					case 2: {
						printf("New x, y and z of origin: ");
						scanf("%f %f", &input1, &input2, &input4);
						trans_pir(triCoordinates[0][0], triCoordinates[0][1], triCoordinates[0][2], triCoordinates[1][0], triCoordinates[1][1], triCoordinates[1][2], triCoordinates[2][0], triCoordinates[2][1], triCoordinates[2][2], triCoordinates[3][0], triCoordinates[3][1], triCoordinates[3][2], (int)input1, (int)input2, (int)input4, triCoordinates);
						break;
					}
					case 3: {
						printf("Angle of rotation: ");
						scanf("%f", &input1);
						rotate_pir(triCoordinates[0][0], triCoordinates[0][1], triCoordinates[0][2], triCoordinates[1][0], triCoordinates[1][1], triCoordinates[1][2], triCoordinates[2][0], triCoordinates[2][1], triCoordinates[2][2], triCoordinates[3][0], triCoordinates[3][1], triCoordinates[3][2], (int)input1, triCoordinates);
						break;
					}
					case 4: {
						printf("Shearing vectors for x, y and z: ");
						scanf("%f %f %f", &input1, &input2, &input4);
						shear_pir(triCoordinates[0][0], triCoordinates[0][1], triCoordinates[0][2], triCoordinates[1][0], triCoordinates[1][1], triCoordinates[1][2], triCoordinates[2][0], triCoordinates[2][1], triCoordinates[2][2], triCoordinates[3][0], triCoordinates[3][1], triCoordinates[3][2], input1, input2, input4, triCoordinates);
						break;
					}
					default: {
						printf("Wrong entry!!\n");
						--loop;
					}
				}
				printf("Operation %d done\n", loop+1);
			}
			initgraph(&gd, &gm, NULL);
			drawgrid();
			draw_pir(triCoordinates[0][0], triCoordinates[0][1], triCoordinates[0][2], triCoordinates[1][0], triCoordinates[1][1], triCoordinates[1][2], triCoordinates[2][0], triCoordinates[2][1], triCoordinates[2][2], triCoordinates[3][0], triCoordinates[3][1], triCoordinates[3][2]);
			delay(2000);
			closegraph();
			break;
		}
		default: printf("Wrong Entry!!\n");
	}
	return 0;
}