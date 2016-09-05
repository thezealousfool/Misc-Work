#include <stdio.h>
#include <math.h>
#define ERROR 0.0000001

double f(double x) {
	return exp(x) - 2*x - 1;
}

double df(double x) {
	return exp(x) - 2;
}

double ddf(double x) {
	return exp(x);
}

double get_point(double x) {
	return x - f(x) / df(x);
}

int main() {
	double point, prev_point, error, prev_error;
	int iteration = 0;
	FILE *file;

	file = fopen("newton.dat", "w");
	printf("Enter starting point: ");
	scanf("%lf", &point);
	prev_point = 0.0;
	error = 0.0;
	prev_error = 0.0;

	printf("i\t    x\t\t    f(x)\t     e\t\t    o.c\n");

	while (fabs(f(point)) >= ERROR) {
		if (f(point)*ddf(point)/(df(point)*df(point)) >= 1) {
			printf("Error! The function won't converge for this value of starting point\n\n");
			printf("Enter starting point: ");
			scanf("%lf", &point);
			prev_point = 0.0;
			error = 0.0;
			prev_error = 0.0;
			iteration = 0;			
			printf("i\t    x\t\t    f(x)\t     e\t\t    o.c\n");
		}
		++iteration;
		prev_point = point;
		point = get_point(point);
		prev_error = error;
		error = fabs(point - prev_point);
		if (iteration == 1) {
			printf("%d\t%9.7f\t%9.7f\t%9.7f\t    ----\n", iteration, prev_point, f(prev_point), error);
		}
		else {
			printf("%d\t%9.7f\t%9.7f\t%9.7f\t%9.7f\n", iteration, prev_point, f(prev_point), error, fabs(log(error)/log(prev_error)));
		}
		fprintf(file, "%9.7f %9.7f\n", prev_point, f(prev_point));
	}

	printf("Root is at %9.7f\n", point);
	return 0;
}