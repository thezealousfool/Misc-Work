#include <stdio.h>
#include <string.h>

struct student_entry {
    char first_name[50], last_name[50];
    unsigned int roll_number, phone_number;
};

typedef struct student_entry student;

int first_name_asc (student s1, student s2) {
	return strcmp(s1.first_name, s2.first_name) > 0 ? 1 : 0;
}

int first_name_desc (student s1, student s2) {
	return strcmp(s1.first_name, s2.first_name) < 0 ? 1 : 0;
}

int last_name_asc (student s1, student s2) {
	return strcmp(s1.last_name, s2.last_name) > 0 ? 1 : 0;
}

int last_name_desc (student s1, student s2) {
	return strcmp(s1.last_name, s2.last_name) < 0 ? 1 : 0;
}

int roll_asc (student s1, student s2) {
    return s1.roll_number > s2.roll_number;
}

int roll_desc (student s1, student s2) {
    return s1.roll_number < s2.roll_number;
}

/* void bubble_sort (student *data, int start, int end, int (*compare)(student s1, student s2);
*/

int populate_dataset (student *dataset) {
	strcpy(dataset[0].first_name, "Vivek");
	strcpy(dataset[0].last_name, "Roy");
	dataset[0].roll_number = 32;

	strcpy(dataset[1].first_name, "Soumyadeep");
	strcpy(dataset[1].last_name, "Kundu");
	dataset[1].roll_number = 26;

	strcpy(dataset[2].first_name, "Dibyadwati");
	strcpy(dataset[2].last_name, "Lahiri");
	dataset[2].roll_number = 35;

	strcpy(dataset[3].first_name, "Baidik");
	strcpy(dataset[3].last_name, "Chandra");
	dataset[3].roll_number = 15;

	return 4;
}

void swap (student *s1, student *s2) {
	student temp;
	temp = *s1;
	*s1 = *s2;
	*s2 = temp;
}

void bubble_sort (student *data, int start, int end, int (*compare)(student a, student b)) {
	int no_of_iterations = end - start;
	int loop;
	if (start >= end) {
		return;
	}
	while (no_of_iterations--) {
		for (loop = start; loop < end; ++loop) {
			if(compare(data[loop], data[loop+1]))
				swap(data+loop, data+loop+1);
		}
	}
}

int main () {

    student dataset[50];
    int no_of_students, loop;

    no_of_students = populate_dataset(dataset);

    /*// for sorting by first name
    */
	bubble_sort(dataset, 0, no_of_students - 1, first_name_asc);
	for (loop = 0; loop < no_of_students; ++loop) {
		printf("%s %s \t %d\n", dataset[loop].first_name, dataset[loop].last_name, dataset[loop].roll_number);
	}
	printf("\n");

	/*// for sorting by roll number
	*/
	bubble_sort(dataset, 0, no_of_students - 1, roll_asc);
	for (loop = 0; loop < no_of_students; ++loop) {
		printf("%s %s \t %d\n", dataset[loop].first_name, dataset[loop].last_name, dataset[loop].roll_number);
	}
	printf("\n");

    return 0;
}


/*
// takes 2 integer pointers and returns 1
// if the value at the first address is
// lesser than the value at the second address
*/
int lesser_than (int *a, int *b);
/*
// takes 2 integer pointers and returns 1
// if the value at the first address is
// greater than the value at the second address
*/
int greater_than (int *a, int *b);

/*
// takes 2 integer pointers and
// swaps the value at the 2 addresses
*/
/*void swap (int *a, int *b);
*/

/*
// takes an array of integers, start index, end index
// and a compare function. It then uses bubble sorting
// to sort the data from start till end indices
// using the compare function
*/
/*void bubble_sort (int *data, int start, int end, int (*compare)(int*,int*));
*/

/*int main() {
	int data[8] = {20, 35, 30, 72, 81, 22, 66, 17};
	int i;
	bubble_sort(data, 0, 7, lesser_than);
	for (i = 0; i < 8; ++i) {
		printf("%d ", data[i]);
	}
	printf("\n");
	return 0;
}

int lesser_than (int *a, int *b) {
	return *a < *b;
}

int greater_than (int *a, int *b) {
	return *a > *b;
}

void swap (int *a, int *b) {
	int temp;
	temp = *a;
	*a = *b;
	*b = temp;
}

void bubble_sort (int *data, int start, int end, int (*compare)(int*,int*)) {
	int no_of_iterations = end - start;
	int loop;
	if (start >= end) {
		return;
	}
	while (no_of_iterations--) {
		for (loop = start; loop < end; ++loop) {
			if(compare(data+loop, data+loop+1))
				swap(data+loop, data+loop+1);
		}
	}
}*/
