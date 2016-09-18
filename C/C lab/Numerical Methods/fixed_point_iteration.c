#include <stdio.h>
#include <math.h>

// double g (double x) {
// 	return sqrt(exp(x) / 4.0);
// }

// double g2 (double x) {
//     return -1.0 * sqrt(exp(x) / 4.0);
// }

// double g3 (double x) {
//     return log(4*x*x) / log(exp(1));
// }

// double dg (double x) {
// 	return (exp(x/2) / 4.0);
// }

// double dg2 (double x) {
//     return -1.0*(exp(x/2) / 4.0);
// }

// double dg3 (double x) {
//     return 1.0/(4.0*x*x)*8.0*x;
// }

// double f (double x) {
// 	return exp(x) - 4*x*x;
// }

double f (double x) {
    return (pow(x,4)) - x - 10;
}

double g1 (double x) {
    return 10.0/(pow(x, 3) - 1);
}

double g2 (double x) {
    return sqrt(sqrt(x + 10.0));
}

double dg1 (double x) {
    return (-30.0*pow(x,2))/pow(pow(x,3) - 1,2);
}

double dg2 (double x) {
    return 0.25*pow(x+10, -0.75);
}

int main() {
	int iteration, choice;
	double x, prev_x, error_tolerance, error, prev_error;
    FILE *file;

    file = fopen("fixed.dat", "w");
	x = prev_x = error = prev_error = 0.0; iteration = 0;
	error_tolerance = 0.0000001;

	printf("Enter starting point: ");
	scanf("%lf", &x);
    printf("Enter choice: ");
    scanf("%d", &choice);

    printf("  i\t    xi\t          g(xi)\t           f(xi)\t    e\t           o.c\n\n");
    do {
    	++iteration;
    	prev_x = x;
        if (choice == 1) {
        	if (fabs(dg1(prev_x)) >= 1.0) {
        		printf("Diverges! Aborting\n");
        		return 1;
        	}
            x = g1(prev_x);
        }
        else {
            if (fabs(dg2(prev_x)) >= 1.0) {
                printf("Diverges! Aborting\n");
                return 1;
            }
            x = g2(prev_x);
        }
    	prev_error = error;
    	error = fabs(x - prev_x);
    	if (iteration == 1) {
	    	printf("%3d\t%9.7f\t%9.7f\t%9.7f\t%9.7f\t   ----\n", iteration, prev_x, fabs(x), f(prev_x), error);
    	}
        else {
    	   printf("%3d\t%9.7f\t%9.7f\t%9.7f\t%9.7f\t%9.7f\t\n", iteration, prev_x, fabs(x), f(prev_x), error, fabs(log(error) / log(prev_error)));
        }
        fprintf(file, "%lf %lf\n", prev_x, f(prev_x));
    } while (fabs(f(x)) >= error_tolerance);

	return 0;
}