#include <math.h>
#include <stdio.h>
#define N 4

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

		printf("Augmented matrix: \n");
		for (inner_loop = 0; inner_loop < n; ++inner_loop) {
			for (inner_loop_elems = 0; inner_loop_elems < n+1; ++inner_loop_elems)
				printf("%8.3f ", mat[inner_loop][inner_loop_elems]);
			printf("\n");
		}

		printf("\n");

	}
	return 0;
}

int main() {
	int loop, inner_loop;

	float mat[N][N+1] = { {  1,    1,   -1,    1,   2},
						  {  2,    1,    1,   -3,   1},
						  {  3,   -1,   -1,    1,   2},
						  {  5,    1,    3,   -2,   7} };

	if (gauss_elimination(N, mat)) {
		printf("Non-singular Matrix\nAborting\n\n");
		return 1;
	}

	upper_triangular_solution(N, mat);

	for (loop = 0; loop < N; ++loop) {
		printf("x%d : %f\n", loop+1, mat[loop][N]);
	}
	printf("\n");
	return 0;
}
