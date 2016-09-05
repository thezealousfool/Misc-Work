#include <stdio.h>

void fibonacci (int first_number, int second_number, int terms) {
	if (terms==1) {
		printf("%d ", second_number);
	}
	else {
		printf("%d ", second_number);
		fibonacci(second_number, first_number+second_number, terms-1);
	}
}

int main() {
	int terms, first_number, second_number;
	printf("Finding fibonacci using iterations\n");
	printf("Enter number of terms of fibonacci series: \n");
	scanf("%d", &terms);
	first_number = 1;
	second_number = 1;
	if (terms>=1) {
		printf("%d ", first_number);
	}
	if (terms>=2) {
		printf("%d ", second_number);
	}
	if(terms>2) {
		terms -= 2;
		while (terms--) {
			second_number = first_number + second_number;
			first_number = second_number - first_number;
			printf("%d ", second_number);
		}
	}
	printf("\n\n");
	printf("Finding fibonacci using recursion\n");
	printf("Enter number of terms of fibonacci series: \n");
	scanf("%d", &terms);
	first_number = 1;
	second_number = 1;
	if (terms>=1) {
		printf("%d ", first_number);
	}
	if (terms>=2) {
		printf("%d ", second_number);
	}
	if (terms>2) {
		fibonacci(1,2, terms-2);
	}
	return 0;
}