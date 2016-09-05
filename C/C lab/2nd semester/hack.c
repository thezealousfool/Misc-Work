#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define NAME_LENGTH 51
#define NO_OF_SUBJECTS 2

struct  student_details {
	char name[NAME_LENGTH], subject_names[NO_OF_SUBJECTS][NAME_LENGTH];
	int class, marks[NO_OF_SUBJECTS];
};

typedef struct student_details entry;
void input_database (entry* database, int no_of_students) {
	int loop1, loop2;
	printf("\nDatabase Entry: \n\n");
	for (loop1=0; loop1<no_of_students; ++loop1) {
		printf("Student number %d:\n", loop1+1);
		printf("Name: ");
		scanf("%50[^\n]", database[loop1].name);
		getchar();
		printf("Class: ");
		scanf("%d", &database[loop1].class);
		getchar();
		for (loop2=0; loop2<NO_OF_SUBJECTS; ++loop2) {
			printf("\n");
			printf("Subject %d name: ", loop2+1);
			scanf("%50[^\n]", database[loop1].subject_names[loop2]);
			getchar();
			printf("Subject %d marks: ", loop2+1);
			scanf("%d", &database[loop1].marks[loop2]);
			getchar();
		}
		printf("\n");
	}
}

void print_database (entry* database, int no_of_students) {
	int loop1, loop2;
	printf("Database: \n\n");
	for (loop1=0; loop1<no_of_students; ++loop1) {
		printf("Student number %d:\n", loop1+1);
		printf("Name: %s\n", database[loop1].name);
		printf("Class: %d\n", database[loop1].class);
		for (loop2=0; loop2<NO_OF_SUBJECTS; ++loop2) {
			printf("\n");
			printf("Subject %d name: %s\n", loop2+1, database[loop1].subject_names[loop2]);
			printf("Subject %d marks: %d\n", loop2+1, database[loop1].marks[loop2]);
		}
		printf("\n");
	}
}

int main(void) {
	int no_of_students;
	int loop1, loop2;
	entry *database;
	printf("Number of students in database: ");
	scanf("%d", &no_of_students);
	getchar();
	database = malloc(no_of_students*sizeof(entry));
	input_database(database, no_of_students);
	print_database(database, no_of_students);
	printf("\n\n");
	printf("\nHacking...............\n");
	srand(time(NULL));
	int student1 = rand()%no_of_students;
	int subject_no1 = rand()%NO_OF_SUBJECTS;
	int student2 = rand()%no_of_students;
	int subject_no2 = rand()%NO_OF_SUBJECTS;
	printf("Swapping marks of student %d's subject %d marks with student %d's subject %d marks\n", student1+1, subject_no1+1, student2+1, subject_no2+1);
	int temp = database[student1].marks[subject_no1];
	database[student1].marks[subject_no1] = database[student2].marks[subject_no2];
	database[student2].marks[subject_no2] = temp;
	printf("\n"); print_database(database, no_of_students);
	return 0;
}