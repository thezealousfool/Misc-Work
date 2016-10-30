#include <stdio.h>
#define MAX 100

int list_length(int* list) {
	return list[0];
}

int add_element(int* list, int element) {
	if (list_length(list) >= (MAX))
		return -1;

	list[++list[0]] = element;
	return 1;
}

int is_empty(int* list) {
	if(list_length(list) == 0) {
		return 1;
	}
	return 0;
}

int nth_read(int* list, int n) {
	if(n > list_length(list)) {
		return -2;
	}
	return list[n];
}

int nth_change(int* list, int n, int val) {
	if(n > list_length(list)) {
		return -2;
	}
	list[n] = val;
	return 1;
}

int insert_n(int* list, int n, int val) {
	int i, len;
	len = list_length(list);
	if (n > len)
		return -2;
	if(len >= MAX)
		return -1;
	for(i = len+1; i > n; --i) {
		list[i] = list[i-1];
	}
	list[n] = val;
	++list[0];
}

int lin_search(int* list, int val) {
	int i, len;
	len = list_length(list);
	for(i = 1; i <= len; ++i) {
		if(list[i] == val) {
			return i;
		}
	}
	return -1;
}

void bub_sort(int* list, int order) {
	int i, j, len, temp;
	len = list_length(list);
	if(order > 0)
		order = 1;
	else
		order = -1;
	for(i = 1; i <= len; ++i) {
		for(j = 1; j < len; ++j) {
			if((order*list[j]) > (order*list[j+1])) {
				temp = list[j+1];
				list[j+1] = list[j];
				list[j] = temp;
			}
		}
	}
}

void p_list(int* list) {
	int i, len;
	len = list_length(list);
	for(i = 1; i <= len; ++i) {
		printf("%d  ", list[i]);
	}
	printf("\n\n");
}

int main() {
	int choice;
	int number = 0, temp, code;
	int list[MAX+1];
	for(temp = 0; temp < MAX+1; ++temp)
		list[temp] = 0;

	printf("1. Add elements to the list\n");
	printf("2. Check if the list is empty\n");
	printf("3. Find length of the list\n");
	printf("4. Read the nth element of the list\n");
	printf("5. Change the nth element of the list\n");
	printf("6. Insert element at position n of the list\n");
	printf("7. Search for a value in the list\n");
	printf("8. Sort the list\n");
	printf("9. Print the list\n");
	printf("0. Exit\n\n");

	while(1) {

		printf("Choice: ");
		scanf("%d", &choice);
		getchar();

		switch(choice) {
			case 0:		return 0;
			case 1:		printf("Value: ");
						scanf("%d", &temp);
						getchar();
						if((code = add_element(list, temp)) > 0)
							printf("Successful!\n\n");
						else if (code == -1)
							printf("ERROR:\tOverflow\n\n");
						break;
			case 2:		if (is_empty(list))
							printf("Empty!\n\n");
						else
							printf("Not Empty!\n\n");
						break;
			case 3:		temp = list_length(list);
						printf("Length: %d\n\n", temp);
						break;
			case 4:		printf("N: ");
						scanf("%d", &temp);
						getchar();
						code = nth_read(list, temp);
						if(code == -2)
							printf("ERROR:\tInvalid Position %d!\n\n", temp);
						else
							printf("Nth Element: %d\n\n", code);
						break;
			case 5:		printf("N: ");
						scanf("%d", &temp);
						getchar();
						printf("New value: ");
						scanf("%d", &code);
						getchar();
						code = nth_change(list, temp, code);
						if(code == -2)
							printf("ERROR:\tInvalid Position %d!\n\n", temp);
						else
							printf("Successful!\n\n");
						break;
			case 6:		printf("N: ");
						scanf("%d", &temp);
						getchar();
						printf("Value: ");
						scanf("%d", &code);
						getchar();
						code = insert_n(list, temp, code);
						if(code == -2)
							printf("ERROR:\tInvalid Position %d!\n\n", temp);
						else if(code == -1)
							printf("ERROR:\tOverflow!\n\n");
						else
							printf("Successful!\n\n");
						break;
			case 7:		printf("Search: ");
						scanf("%d", &temp);
						getchar();
						code = lin_search(list, temp);
						if(code == -1)
							printf("No element found\n\n");
						else
							printf("Element found at position %d\n\n", code);
						break;
			case 8:		printf("1 for ascending, -1 for descending\n");
						printf("Order: ");
						scanf("%d", &temp);
						getchar();
						bub_sort(list, temp);
						printf("Done!\n\n");
						break;
			case 9:		printf("List: ");
						p_list(list);
						break;
			default:	printf("ERROR:\tWrong Entry!\n\n");
		}
	}
	return 0;
}