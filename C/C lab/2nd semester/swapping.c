#include <stdio.h>
#include <stdlib.h>

void swap (int* array, int index1, int index2) {
	int temp = array[index1];
	array[index1] = array[index2];
	array[index2] = temp;
}

void print_array (int* array, int no_of_elements) {
	int loop;
	for (loop = 0; loop<no_of_elements; ++loop)
		printf("%d ", array[loop] );
	printf("\n");
}

int main() {
	int *new_array, *array, index1, index2, index;
	int no_of_elements;
	printf("Number of elements in the array: \n");
	scanf("%d", &no_of_elements);
	array = malloc (no_of_elements*sizeof(int));
	printf("Enter array elements: \n");
	for(index = 0; index<no_of_elements; ++index) 
		scanf("%d", &array[index]);
	printf("\n\n");
	printf("Array before swapping: \n");
	print_array(array, no_of_elements);
	printf("Swapping without pointer\nEnter 2 indexes:\n");
	scanf("%d %d", &index1, &index2);
	int temp = array[index1];
	array[index1] = array[index2];
	array[index2] = temp;
	print_array(array, no_of_elements);
	printf("Swapping with pointer\nEnter 2 indexes:\n");
	scanf("%d %d", &index1, &index2);
	swap(array, index1, index2);
	printf("\nArray after swapping: \n");
	print_array(array, no_of_elements);
	return 0;
}