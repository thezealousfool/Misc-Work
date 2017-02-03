#include <stdio.h>

int fibonacci (int index) {
	if (index <= 1) {
		return 0;
	}
	if (index == 2) {
		return 1;
	}
	return fibonacci(index - 1) + fibonacci(index - 2);
}

int main() {
	int required_location, location = 2, value = 0, a = 0, b = 1, c = 0;
	char choice = 'i';
	printf("Enter n: ");
	scanf("%d", &required_location);

	if (required_location < 0) {
		printf("Negative index not defined\n");
		return 1;
	}

	printf("Enter i for iterative method, r for recursive method: ");
	getchar();
	scanf("%c", &choice);
	if (choice == 'i') {
		printf("\nIterative method:\n");
		printf("n-th fibonacci no: ");
		if (required_location <= 2) {
			if (required_location == 1) {
				printf("%d\n", a);
				return 0;
			}
			else {
				printf("%d\n", b);
				return 0;
			}
		}

		do {
			c = a + b;
			a = b;
			b = c;
			++location;
		} while (location < required_location);

		printf("%d\n", b);
		return 0;
	}
	else if (choice == 'r') {
		printf("\nRecursive method:\n");
		printf("n-th fibonacci no: ");

		printf("%d\n", fibonacci(required_location));
		return 0;
	}
	else {
		printf("Wrong entry!\n");
		return 1;
	}
}