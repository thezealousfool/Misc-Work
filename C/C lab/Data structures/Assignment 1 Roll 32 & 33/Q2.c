/*
Q. Write a program to compute the factorial of an integer
   iteratively and recursively.
*/
#include <stdio.h>

int find_factorial(int n) {
	if (n == 1 || n == 0) 
		return 1;
	return n * find_factorial(n-1);
}

int main() {
	int factorial = 1, n, loop;
	char choice = 'r';
	printf("Enter n: ");
	scanf("%d", &n);

	if (n < 0) {
		printf("Factorial of a negative number not defined\n");
		return 1;
	}

	getchar();
	printf("Enter i for iterative method r for recursive method\nEnter choice: ");
	scanf("%c", &choice);

	if (choice == 'i') {
		printf("Iterative method:\n");
		for (loop = 1; loop <= n; ++loop) {
			factorial *= loop;
		}
		printf("Factorial: %d\n", factorial);
		return 0;
	}
	else if (choice == 'r') {
		printf("Recursive method:\n");
		factorial = find_factorial(n);
		printf("Factorial: %d\n", factorial);
		return 0;
	}
	else {
		printf("Wrong Entry!\n");
		return 1;
	}
}