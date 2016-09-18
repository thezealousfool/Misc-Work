#include <stdio.h>
#include <math.h>

double new_x (double xi_m1, double xi, double xi_p1) {
	return xi_p1 - (pow(xi_p1 - xi, 2))/(xi_p1 - 2*xi + xi_m1);
}

double f (double x) {
	return cos(x) - 2*x + 3;
}

double g (double x) {
	return 0.5*(cos(x) + 3);
}

double dg (double x) {
	return 0.5*sin(x);
}

int main() {
	int iteration = 0;
	double x = 0.0, prev_x = 0.0, next_x = 0.0, prev_x_atk = 0.0, temp = 0.0, error = 0.0, prev_error = 0.0;
	double error_tolerance = 0.00005;
	FILE *file;

	printf("Enter starting point: ");
	scanf("%lf", &prev_x);
	x = g(prev_x);
	next_x = g(x);

	file = fopen("aitken.dat", "w");
    printf("  i\t    xi\t          f(xi)\t\t    e\t           o.c\n\n");

	do {
		++iteration;
		prev_x_atk = prev_x;
		prev_x = new_x(prev_x, x, next_x);
		x = g(prev_x);
		next_x = g(x);
		prev_error = error;
		error = fabs(prev_x - prev_x_atk);
		if (fabs(dg(x)) >= 1) {
			printf("Error!! Won't converge!\n");
			return 1;
		}
		if (iteration == 1) {
	    	printf("%3d\t%9.7f\t%9.7f\t%9.7f\t   ----\n", iteration, prev_x, f(prev_x), error);
		}
		else {
    		printf("%3d\t%9.7f\t%9.7f\t%9.7f\t%9.7f\n", iteration, prev_x, f(prev_x), error, fabs(log(error) / log(prev_error)));
    	}
    	fprintf(file, "%lf %lf\n", prev_x, f(prev_x));
	} while (fabs(f(x)) >= error_tolerance && error >= error_tolerance);
	printf("Root: %lf\n", x);
	return 0;
}