#include <stdio.h>
#include <math.h>
#define P 2

double f(double x) {
	return pow(x, 3) - pow(x, 2) - x + 1;
}

double df(double x) {
	return 3*pow(x, 2) - 2*x - 1;
}

double ddf(double x) {
	return 6*x - 2;
}

double new_x(double x, int p) {
	return x - p*(f(x)/df(x));
}

double new_x_2(double x, int p) {
	return x - p*(df(x)/ddf(x));
}

int main() {
	int iteration = 0;
	double x = 0.0, x2 = 0.0, prev_x = 0.0, error = 0.0, prev_error = 0.0;
	double error_tolerance = 0.00005;
	FILE *file;

	printf("Enter starting point: ");
	scanf("%lf", &x);
	if (fabs(1-P+(P*f(x)*ddf(x)/(df(x)*df(x)))) >= 1) {
		printf("Bad Starting point\nTry again!\n\n");
		return 1;
	}

	file = fopen("gen_newton.dat", "w");
    printf("  i\t    xi\t          f(xi)\t\t    e\t           o.c\n\n");

	do {
		++iteration;
		prev_x = x;
		x = new_x(x, 2);
		x2 = new_x_2(x, 1);
		prev_error = error;
		error = fabs(x - prev_x);
		if (iteration == 1) {
	    	printf("%3d\t%9.7f\t%9.7f\t%9.7f\t   ----\n", iteration, prev_x, f(prev_x), error);
		}
		else {
    		printf("%3d\t%9.7f\t%9.7f\t%9.7f\t%9.7f\n", iteration, prev_x, f(prev_x), error, fabs(log(error) / log(prev_error)));
    	}
    	fprintf(file, "%lf %lf\n", prev_x, f(prev_x));
	} while (error >= error_tolerance);
	printf("Root: %lf\n", x);
	return 0;
}