#include <stdio.h>
#include <math.h>
#define MAX_ITR 100
#define N 3
#define TOL 0.00000005

int main() {
	float A[N][N], B[N], X[N], err, perr, sum, tmp;
	int i, j, k;
	err = perr = 0.0;
	printf("\nSolving for system AX = B:\n\n");

	printf("Enter matrix A: \n");
	for (i = 0; i < N; ++i)
		for (j = 0; j < N; ++j)
			scanf("%f", &A[i][j]);

	for (i = 0; i < N; ++i) {
		tmp = 0.0;
		for (j = 0; j < N; ++j) {
			if (i != j)
				tmp += fabs(A[i][j]);
		}
		if (tmp >= fabs(A[i][i])) {
			printf("Not Diagonally dominant!!\n\n");
			return -1;
		}
	}

	printf("Enter matrix B: \n");
	for (i = 0; i < N; ++i)
		scanf("%f", &B[i]);

	printf("Enter initial guesses: \n");
	for (i = 0; i < N; ++i)
		scanf("%f", &X[i]);
	
	printf("  n");
	for (j = 0; j < N; ++j)
		printf("        x%d  ", j+1);
	printf("     error\n");

	for (i = 0; i < MAX_ITR; ++i) {
		printf(" %2d", i);
		for (k = 0; k < N; ++k)
			printf("   %9.6f", X[k]);
		printf("   %9.6f\n", fabs(err-perr));
		for (j = 0; j < N; ++j) {
			sum = 0.0;
			tmp = 0.0;
			for (k = 0; k < N; ++k) {
				if (k == j)
					continue;
				sum += A[j][k] * X[k];
			}
			tmp = (B[j] - sum) / A[j][j];
			if (fabs(tmp - X[j]) > tmp) {
				tmp = fabs(tmp - X[j]);
			}
			X[j] = tmp;
		}
		perr = err;
		err = tmp;
		if (fabs(err - perr) <= TOL) {
			break;
		}
	}

	if (i == MAX_ITR && fabs(err - perr) > TOL)
		printf("Doesn't Converge\n\n");

	return 0;
}
