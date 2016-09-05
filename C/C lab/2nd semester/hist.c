#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#define PI 3.14159

double my_sin (double radians, int no_of_terms) {
	int loop1;
	double term, sum;
	sum = 0;
	term = radians;
	for (loop1 = 1; loop1<=no_of_terms; loop1 = loop1+1) {
		sum = sum + term;
		term = (term * -1 * radians * radians) / ((2*loop1)*(2*loop1 + 1));
	}
	return sum;
}

double my_cos (double radians, int no_of_terms) {
	int loop1;
	double term, sum;
	sum = 0;
	term = 1;
	for (loop1 = 1; loop1<=no_of_terms; loop1 = loop1+1) {
		sum = sum + term;
		term = (term * -1 * radians * radians) / ((2*loop1)*(2*loop1 - 1));
	}
	return sum;
}

void error_print_sin(int i, int n) {
	double radians, error;
	int j;
	radians = PI * i / 180.0;
	error = (my_sin(radians,n)-sin(radians))*22;
	error = abs(error) ;
	//printf("\nsin(%3d)  %2d terms |",i,n);
	//error = (int)error%150;
	for (j=((int)error); j>=0; j = j-1)
		printf("*");
}

void error_print_cos(int i, int n) {
	double radians, error;
	int j;
	radians = PI * i / 180.0;
	error = (my_cos(radians,n)-cos(radians))*22;
	error = abs(error) ;
	//printf("\nsin(%3d)  %2d terms |",i,n);
	//error = (int)error%150;
	for (j=((int)error); j>=0; j = j-1)
		printf("*");
}

int main() {
	int i,n;
	double radians;
	scanf("%d",&n);
	printf("\nsin(x):\n");
	for (i=90; i<=360; i = i+10) {
		error_print_sin(i,n);
		printf("\n");
	}
	printf("\n\ncos(x):\n");
	for (i=90; i<=360; i = i+10) {
		error_print_cos(i,n);
		printf("\n");
	}
	return 0;
}
