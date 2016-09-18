#include <stdio.h>
#include <math.h>
#include <stdlib.h>

double function (double x) {
    return x*sin(x) + cos(x);
}

double find_point_falsi (double a, double b) {
    return b - ((function(b) * (a - b)) / (function(a) - function(b)));
}

double find_point_bisection (double a, double b) {
	return (a+b) / 2.0;
}

void compute (int code) {
    double upper_bound,lower_bound,mid_point, prev_mid_point,error_tolerence, error, prev_error;
    int iteration;

    iteration = 0;
    error_tolerence = 0.0000001;
	prev_mid_point = 0.0;
	error = 0.0;
	prev_error = 0.0;

	printf("Lower bound: ");
	scanf("%lf", &lower_bound);

	printf("Upper bound: ");
	scanf("%lf", &upper_bound);

    printf("i\t    a\t            b\t            m\t            f(m)\t    e\t            o.c\n");
    do {
        if (function(lower_bound)*function(mid_point) < 0)
            upper_bound = mid_point;
        else
            lower_bound = mid_point;
        ++iteration;
		if (code == 1) {
	        mid_point = find_point_falsi(lower_bound, upper_bound);
		}
		else {
			mid_point = find_point_bisection(lower_bound, upper_bound);
		}
		error = fabs(mid_point - prev_mid_point);
		if (iteration == 1) {
			printf("%d\t%9.7f\t%9.7f\t%9.7f\t%9.7f\t   ---\t\t    ---\n", iteration, lower_bound, upper_bound, mid_point, function(mid_point));
		}
		else {
			printf("%d\t%9.7f\t%9.7f\t%9.7f\t%9.7f\t%9.7f\t%9.7f\n", iteration, lower_bound, upper_bound, mid_point, function(mid_point), error, fabs(log(error)/log(prev_error)));
		}
		prev_error = error;
		prev_mid_point = mid_point;
    } while (mid_point - lower_bound >= error_tolerence && upper_bound - mid_point >= error_tolerence);

	printf("\n");

}

int main() {

	printf("Regula falsi method:\n");
	compute(1);

	printf("\n");
	printf("Bisection method:\n");
	compute(2);

	return 0;

}
