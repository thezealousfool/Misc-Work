/*
Q. Write programs for linear search and binary search
   for searching integers, floating point numbers
   and words in arrays of respective types.
*/
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define WORD_LENGTH 50
#define NO_OF_WORDS 4

int linear_search_integers (int *array, int no_of_elements, int element) {
	int position;
	for (position = 0; position < no_of_elements; ++position) {
		if (array[position] == element) {
			return position;
		}
	}
	return -1;
}

int binary_search_integers (int *array, int no_of_elements, int element) {
	int lower_bound, upper_bound, mid_point;

	lower_bound = 0;
	upper_bound = no_of_elements - 1;

	do {
		mid_point = (lower_bound + upper_bound) / 2;
		if (array[mid_point] == element) {
			break;
		}
		if (array[mid_point] > element) {
			upper_bound = mid_point;
		}
		else if (array[mid_point] < element) {
			lower_bound = mid_point;
		}
	} while (mid_point != upper_bound && mid_point != lower_bound);

	if (array[mid_point] == element)
		return mid_point;
	else
		return -1;
}

int linear_search_floats (float *array, int no_of_elements, float element) {
	int position;
	for (position = 0; position < no_of_elements; ++position) {
		if (array[position] == element) {
			return position;
		}
	}
	return -1;	
}

int binary_search_floats (float *array, int no_of_elements, float element) {
	int lower_bound, upper_bound, mid_point;

	lower_bound = 0;
	upper_bound = no_of_elements - 1;

	do {
		mid_point = (lower_bound + upper_bound) / 2;
		if (array[mid_point] == element) {
			break;
		}
		if (array[mid_point] > element) {
			upper_bound = mid_point;
		}
		else if (array[mid_point] < element) {
			lower_bound = mid_point;
		}
	} while (mid_point != upper_bound && mid_point != lower_bound);

	if (array[mid_point] == element)
		return mid_point;
	else
		return -1;
}

int linear_search_words (int no_of_elements, char array[no_of_elements][WORD_LENGTH], char element[WORD_LENGTH]) {
	int position;
	for (position = 0; position < no_of_elements; ++position) {
		if (strcmp(array[position], element) == 0) {
			return position;
		}
	}
	return -1;		
}

int binary_search_words (int no_of_elements, char array[no_of_elements][WORD_LENGTH], char element[WORD_LENGTH]) {
	int lower_bound, upper_bound, mid_point;

	lower_bound = 0;
	upper_bound = no_of_elements - 1;

	do {
		mid_point = (lower_bound + upper_bound) / 2;
		if (strcmp(array[mid_point], element) == 0) {
			break;
		}
		if (strcmp(array[mid_point], element) > 0) {
			upper_bound = mid_point;
		}
		else if (strcmp(array[mid_point], element) < 0) {
			lower_bound = mid_point;
		}
	} while (mid_point != upper_bound && mid_point != lower_bound);

	if (strcmp(array[mid_point], element) == 0)
		return mid_point;
	else
		return -1;
}

int main() {
	char words[NO_OF_WORDS][WORD_LENGTH], element[WORD_LENGTH];
	int found_at;
	int loop;

	printf("Enter %d words: \n", NO_OF_WORDS);
	for (loop = 0; loop < NO_OF_WORDS; ++loop) {
		scanf("%s", words[loop]);
	}
	printf("Enter word to searched: ");
	scanf("%s", element);

	found_at = linear_search_words(NO_OF_WORDS, words, element);
	if (found_at == -1) {
		printf("Word not found!\n");
	}
	else {
		printf("Word found at position %d\n", found_at+1);
	}
	return 0;
}