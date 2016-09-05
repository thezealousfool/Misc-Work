#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define LENGTH 30000

void swap(int* a, int* b) {
	int temp;
	temp = *a;
	*a = *b;
	*b = temp;
}

int main() {
	int array[LENGTH], loop;
	srand(time(NULL));
	for (loop = 0; loop < LENGTH; ++loop) {
		array[loop] = loop+1;
	}
	for (loop = LENGTH - 1; loop > 0; --loop) {
		swap(&array[loop], &array[rand() % loop]);
	}
	for (loop = 0; loop < LENGTH; ++loop) {
		printf("%d\n", array[loop]);
	}
	return 0;
}
