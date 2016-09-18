/*
Q. Write a program to generate 30000 random integers
   between 1 and 30000 without repeatation and store
   them in a file in character mode, 1 number per line.
   Study and use the functions in C related to random
   numbers.
*/
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
	FILE *file;
	
	srand(time(NULL));
	file = fopen("Q4.txt", "w");
	for (loop = 0; loop < LENGTH; ++loop) {
		array[loop] = loop+1;
	}
	for (loop = LENGTH - 1; loop > 0; --loop) {
		swap(&array[loop], &array[rand() % loop]);
	}
	for (loop = 0; loop < LENGTH; ++loop) {
		fprintf(file, "%d\n", array[loop]);
	}
	return 0;
}
