#include <stdio.h>

int factorial (int number) {
	if (number == 1)
		return 1;
	return number*factorial(number-1);
}

int main() {
	int number, loop, result;
	printf("Finding factorial using iteration...\n");
	printf("Enter number: ");
	scanf("%d", &number);
	result = 1;
	for(int loop=2; loop<=number; ++loop)
		result *= loop;
	printf("Factorial of the number is %d\n\n", result);

	printf("Finding factorial using recursion...\n");
	printf("Enter number: ");
	scanf("%d", &number);
	result = factorial(number);
	printf("Factorial of the number is %d\n\n", result);
	return 0;
}