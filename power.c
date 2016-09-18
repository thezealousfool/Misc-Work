#include <stdio.h>
#include <math.h>
#define N 4
#define ERROR 0.000005

int main(void){
	int i, j, k=0, iter=15;
	float a[N][N], x[N], y[N], max, d, prev_d;
	printf("\nIt's a %dX%d matrix. Enter elements rowwise.\n", N, N);
	for(i = 0; i < N; ++i){
		for(j = 0; j < N; ++j){
			scanf("%f", &a[i][j]);
		}	
	}

	printf("The first value of the eigenvector is being initialized to 1\n");
	x[0] = 1;
	printf("Enter the rest %d values of the eigenvector:\n", N-1);
	for (i = 1; i < N; ++i) {
		scanf("%f", &x[i]);
	}	

	k = 0;
	d = 0.0;
	prev_d = 0.0;
		
	do{
		for(i = 0; i < N; ++i) {
			y[i]=0;
			for(j = 0; j < N; ++j) {
				y[i] = y[i] + a[i][j] * x[j];
			}
		}
		
		max = fabs(y[0]);
		j = 0;
		
		for(i = 0; i < N; ++i) {
			if(fabs(y[i]) >= max){
				max = fabs(y[i]);
				j = i;
			}
		}

		for(i = 0; i < N; ++i){
			x[i] = y[i] / d;
		}
		
		++k;

		printf("\nLargest eigenvalue after iteration %2d is: %9.6f\n", k, d);
		printf("\nLargest eigenvector is: \n");
		for(i = 0; i < N; ++i)
			printf("%9.6f\n",x[i]);
	} while(fabs(d - prev_d) >= ERROR);
	
	printf("\nLargest eigenvalue is: %9.6f\n", d);
	printf("\nLargest eigenvector is: \n");
	
	for(i = 0; i < N; ++i)
		printf("\t%9.6f\n", x[i]);
	
	return 0;
}