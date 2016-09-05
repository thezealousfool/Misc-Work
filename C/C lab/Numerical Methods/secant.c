#include <stdio.h>
#include <math.h>

double f (double x) {
	return exp(x) - 2*x - 1;
}

int main() {
	int iteration = 0;
	double x = 0.0, prev1_x = 0.0, prev2_x = 0.0, error = 0.0, prev_error = 0.0;
	double error_tolerance = 0.0000001;
	FILE *file;

	printf("Enter 2 starting points: \n");
	scanf("%lf %lf", &prev1_x, &x);

	file = fopen("secant.dat", "w");
    printf("  i\t    xi\t          f(xi)\t\t    e\t           o.c\n\n");

	do {
		++iteration;
		prev2_x = prev1_x;
		prev1_x = x;
		x = (prev2_x*f(prev1_x) - prev1_x*f(prev2_x)) / (f(prev1_x) - f(prev2_x));
		prev_error = error;
		error = fabs(x - prev1_x);
		if (iteration == 1) {
	    	printf("%3d\t%9.7f\t%9.7f\t%9.7f\t   ----\n", iteration, prev1_x, f(prev1_x), error);
		}
		else {
    		printf("%3d\t%9.7f\t%9.7f\t%9.7f\t%9.7f\n", iteration, prev1_x, f(prev1_x), error, fabs(log(error) / log(prev_error)));
    	}
    	fprintf(file, "%lf %lf\n", prev1_x, f(prev1_x));
	} while (error >= error_tolerance);
	return 0;
}