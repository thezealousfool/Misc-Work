#include <math.h>
#include <stdio.h>
#define N 3
#define K N

void augment_matrix(int n, float mat[n][n], float aug_mat[n][2*n]) {
	int loop, inner_loop;
	for (loop = 0; loop < n; ++loop) {
		for (inner_loop = 0; inner_loop < n; ++inner_loop)
			aug_mat[loop][inner_loop] = mat[loop][inner_loop];
		for (inner_loop = n; inner_loop < 2*n; ++inner_loop)
			if (loop+n == inner_loop)
				aug_mat[loop][inner_loop] = 1;
			else
				aug_mat[loop][inner_loop] = 0;
	}
}

int gauss_jordon( int n, int k, float mat[n][n+k] ) {
	int loop, inner_loop, inner_loop_elems;
	float factor;
	for (loop = 0; loop < n; ++loop) {

		inner_loop_elems = loop;

		for (inner_loop = loop; inner_loop < n; ++inner_loop) {
			if (fabs(mat[inner_loop][loop]) > fabs(mat[inner_loop_elems][loop]))
					inner_loop_elems = inner_loop;
		}

		for (inner_loop = 0; inner_loop < n; ++inner_loop) {
			for (inner_loop = 0; inner_loop < n+k; ++inner_loop) {
				float temp = mat[inner_loop_elems][inner_loop];
				mat[inner_loop_elems][inner_loop] = mat[loop][inner_loop];
				mat[loop][inner_loop] = temp;
			}
		}

		if (fabs(mat[loop][loop]) >= 0.00001) {
			for (inner_loop = loop+1; inner_loop < n; ++inner_loop) {
				factor = mat[inner_loop][loop] / mat[loop][loop];
				for (inner_loop_elems = 0; inner_loop_elems < n+k; ++inner_loop_elems)
					mat[inner_loop][inner_loop_elems] -= factor*mat[loop][inner_loop_elems];
			}
			factor = mat[loop][loop];
			for (inner_loop_elems = 0; inner_loop_elems < n+k; ++inner_loop_elems)
				mat[loop][inner_loop_elems] /= factor;
			for (inner_loop = 0; inner_loop < loop; ++inner_loop) {
				factor = mat[inner_loop][loop] / mat[loop][loop];
				for (inner_loop_elems = 0; inner_loop_elems < n+k; ++inner_loop_elems)
					mat[inner_loop][inner_loop_elems] -= factor*mat[loop][inner_loop_elems];
			}
		}
		else {
			return 1;
		}

		printf("\nAugmented matrix: \n");
		for (inner_loop = 0; inner_loop < n; ++inner_loop) {
			for (inner_loop_elems = 0; inner_loop_elems < n+k; ++inner_loop_elems)
				printf("%8.3f ", mat[inner_loop][inner_loop_elems]);
			printf("\n");
		}
	}
	return 0;
}

int main() {
	int loop, inner_loop, inner_loop_elems;

	float mat[N][N] = { {1, 5, 3},
						{1, 3, 2},
						{2, 4, -6} };
	float aug_mat[N][N+K];

	augment_matrix(N, mat, aug_mat);
	
	printf("Matrix: \n");
	for (loop = 0; loop < N; ++loop) {
		for (inner_loop = 0; inner_loop < N; ++inner_loop) {
			printf("%8.3f ", aug_mat[loop][inner_loop]);
		}
		printf("\n");
	}

	if (gauss_jordon(N, K, aug_mat)) {
		printf("Non-singular Matrix\nAborting\n\n");
		return 1;
	}

	printf("\n");

	printf("Inverse matrix: \n");

	for (loop = 0; loop < N; ++loop) {
		for (inner_loop = N; inner_loop < N+K; ++inner_loop) {
			printf("%8.3f ", aug_mat[loop][inner_loop]);
		}
		printf("\n");
	}
	printf("\n");
	
	for (loop = 0; loop < N; ++loop)
		for (inner_loop = 0; inner_loop < N; ++inner_loop)
			aug_mat[loop][inner_loop] = 0;

	for (loop = 0; loop < N; ++loop) {
		for (inner_loop = 0; inner_loop < N; ++inner_loop) {
			for (inner_loop_elems = 0; inner_loop_elems < N; ++inner_loop_elems) {
				aug_mat[loop][inner_loop] += aug_mat[inner_loop][inner_loop_elems + N]*mat[inner_loop_elems][inner_loop];
			}
		}
	}

	printf("Multiplying Matrix with its Inverse: \n");

	for (loop = 0; loop < N; ++loop) {
		for (inner_loop = 0; inner_loop < N; ++inner_loop) {
			if (loop != inner_loop)
				aug_mat[loop][inner_loop] -= 1;
			printf("%8.3f ", aug_mat[loop][inner_loop]);
		}
		printf("\n");
	}
	printf("\n");

	return 0;
}
