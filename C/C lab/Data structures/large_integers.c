#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <limits.h>

#define SERIES_LENGTH 20

int main() {
	long int P, L;
	int loop;
	srand(time(NULL));
	printf("Enter a four-digit prime number\n");
	scanf("%ld", &P);
	if (P >= 10000 || P < 1000) {
		printf("The entered number is not 4 digits long\n");
		return 1;
	}
	printf("    Li\t\tRi\n");
	printf("-----------------------\n");
	for (loop = 0; loop < SERIES_LENGTH; ++loop) {
		L = rand() % LONG_MAX;
		printf("%ld\t%ld\n", L, L%P);
	}
	return 0;
}