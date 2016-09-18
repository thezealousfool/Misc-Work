#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#define N 2
#define MAX(X, Y) (((X) < (Y)) ? (X) : (Y))
// f1 : x^2 + x*y - 10
// f2 : y + 3*x*(y^2) - 57

float f1(float x, float y) {
	return x*x + x*y - 10;
}

float f2(float x, float y) {
	return y + 3*x*y*y - 57;
}

float df1_dx(float x, float y) {
	return 2*x + y;
}

float df2_dx(float x, float y) {
	return 3*y*y;
}

float df1_dy(float x, float y) {
	return x;
}

float df2_dy(float x, float y) {
	return 1 + 6*x*y;
}

void upper_triangular_solution( int n, float mat[n][n+1] ) {
	int loop, inner_loop;
	for (loop = n-1; loop >= 0; --loop) {
		for (inner_loop = loop + 1; inner_loop < n; ++inner_loop) {
			mat[loop][n] -= mat[loop][inner_loop]*mat[inner_loop][n];
			mat[loop][inner_loop] = 0;
		}
		mat[loop][n] /= mat[loop][loop];
		mat[loop][loop] = 1;
	}
}

int gauss_elimination( int n, float mat[n][n+1] ) {
	int loop, inner_loop, inner_loop_elems;
	float factor;
	for (loop = 0; loop < n; ++loop) {

		inner_loop_elems = loop;

		for (inner_loop = loop; inner_loop < n; ++inner_loop) {
			if (fabs(mat[inner_loop][loop]) > fabs(mat[inner_loop_elems][loop]))
					inner_loop_elems = inner_loop;
		}

		for (inner_loop = 0; inner_loop < n; ++inner_loop) {
			for (inner_loop = 0; inner_loop < n+1; ++inner_loop) {
				float temp = mat[inner_loop_elems][inner_loop];
				mat[inner_loop_elems][inner_loop] = mat[loop][inner_loop];
				mat[loop][inner_loop] = temp;
			}
		}

		if (fabs(mat[loop][loop]) >= 0.00001) {
			for (inner_loop = loop+1; inner_loop < n; ++inner_loop) {
				factor = mat[inner_loop][loop] / mat[loop][loop];
				for (inner_loop_elems = 0; inner_loop_elems <= n; ++inner_loop_elems)
					mat[inner_loop][inner_loop_elems] -= factor*mat[loop][inner_loop_elems];
			}
		}
		else {
			return 1;
		}

	}
	return 0;
}

int solve_h_k(int n, float mat[n][n+1]) {
	if (gauss_elimination(n, mat)) {
		return 1;
	}
	upper_triangular_solution(n, mat);
	return 0;
}

int main()
{
	int iteration = 0;
	float x0, y0, x1, y1, error = 0.0, perror = 0.0;
	float A[N][N+1];
	printf("Enter initial approximation of x: ");
	scanf("%f", &x1);
	printf("Enter initial approximation of y: ");
	scanf("%f", &y1);
	printf("\n No         x            y          error          h             k\n");
	do {
		x0 = x1;
		y0 = y1;
		++iteration;
		A[0][2] = -1.0*f1(x0, y0);
		A[1][2] = -1.0*f2(x0, y0);
		A[0][0] = df1_dx(x0, y0);
		A[0][1] = df1_dy(x0, y0);
		A[1][0] = df2_dx(x0, y0);
		A[1][1] = df2_dy(x0, y0);
		if (solve_h_k(N, A)) {
			printf("Cannot find solution for these values\nAborting!!\n");
			return 1;
		}
		x1 = x0 + A[0][2];
		y1 = y0 + A[1][2];
		error = MAX(fabs(x1 - x0), fabs(y1 - y0));
		printf("%3d  %12.6f %12.6f %12.6f %12.6f %12.6f\n", iteration, x0, y0, error, A[0][2], A[1][2]);
	} while (error >= 0.0000005);
	printf("\n\nSolution:\nx: %9.6f\ny: %9.6f\n", x1, y1);
	return 0;
}