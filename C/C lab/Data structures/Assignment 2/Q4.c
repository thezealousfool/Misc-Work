/**
* Write a menu driven program which performs the following operations on a character string without using
* any inbuilt function in C.
**/
#include <stdio.h>
#include <stdlib.h>
#define MAX_NO 100

// create a new string and return the pointer to the first element of the string
char* create (int length) {
	char* s = (char*)malloc((length+1)*sizeof(char));
	if (s == NULL)
		return NULL;
	s[0] = length;
	return s;
}

// initialize a new string by taking input from the user
char* init() {
	int length, i;
	char ch;
	char* str;
	printf("Length(max 255): ");
	scanf("%d", &length);
	getchar();
	if(length > 255) {
		printf("ERROR:\tOverflow! String exceeding 255 characters!\n\n");
		return NULL;
	}
	str = create(length);
	if (str == NULL) {
		printf("ERROR:\tAllocation Error.\n\n");
		return NULL;
	}
	printf("String (%d characters): ", length);
	for (i = 1; i <= length; ++i) {
		ch = getchar();
		if(ch == '\n')
			break;
		str[i] = ch;
	}
	if(!(i > length)) {
		printf("\nEntered String is %d characters long!\n", i-1);
		printf("Resizing!\n");
		str = realloc(str, i);
		str[0] = i-1;
	}
	else {
		while(getchar() != '\n');
	}
	printf("Success!\n\n");
	return str;
}

// print a string to the std output stream
void print(char* s) {
	if (s == NULL) {
		printf("ERROR:\tNULL String\n\n");
		return;
	}
	int len = s[0], i;
	for (i = 1; i <= len; ++i) {
		printf("%c", s[i]);
	}
}

// returns the length of a string
int	length(char* s) {
	if (s == NULL) {
		printf("ERROR:\tNULL String\n\n");
		return -1;
	}
	return (int)s[0];
}

// compares to strings and returns +1 if s2 > s1, 0 if s2 = s1 and -1 if s2 < s1
int compare(char* s1, char* s2) {
	int till, i;
	if(s1 == NULL && s2 == NULL) {
		printf("ERROR:\tComparison of two NULL Strings is undefined\n\n");
		return 2;
	}
	if(s1 == NULL) {
		printf("ERROR:\tFirst string is NULL\n\n");
		return 2;
	}
	if(s2 == NULL) {
		printf("ERROR:\tSecond string is NULL\n\n");
		return 2;
	}
	till = s1[0] < s2[0] ? s1[0] : s2[0];
	for (i = 1; i <= till; ++i) {
		if (s1[i] < s2[i])
			return 1;
		else if(s1[i] > s2[i])
			return -1;
	}
	if (s1[0] == s2[0])
		return 0;
	else if (till == s1[0])
		return 1;
	else
		return -1;
}

// creates and returns a new string which is formed after concatinating two strings
char* concat(char* s1, char* s2) {
	int i, len1, len2;
	char *s;
	if(s1 == NULL) {
		if(s2 == NULL) {
			printf("ERROR:\tBoth strings are NULL\n\n");
			return NULL;
		}
		else
			len1 = 0;
	}
	else {
		if(s2 == NULL)
			len2 = 0;
		else {
			len1 = s1[0];
			len2 = s2[0];
		}
	}
	if (len1 + len2 > 255) {
		printf("ERROR:\tOverflow! String exceeding 255 characters!\n\n");
		return NULL;
	}
	s = create(len1+len2);
	if (s == NULL) {
		printf("ERROR:\tAllocation Error.\n\n");
		return NULL;
	}
	for(i = 1; i <= len1; ++i) {
		s[i] = s1[i];
	}
	for(i = 1; i <= len2; ++i) {
		s[len1+i] = s2[i];
	}
	printf("Success!\n\n");
	return s;
}

// copy the contents of the first string into the second string (should be long enough)
char* copy(char* s1, char* s2) {
	int i, len1;
	if(s1 == NULL || s2 == NULL) {
		printf("ERROR:\tBoth strings are NULL\n\n");
		return NULL;
	}
	if(s1 == NULL) {
		s2 = NULL;
		return s2;
	}
	if(s2 == NULL) {
		printf("ERROR:\tCannot copy into a NULL string\n\n");
		return NULL;
	}
	len1 = s1[0];
	if (len1 > s2[0]) {
		printf("ERROR:\tSecond string is not long enough\n\n");
		return NULL;
	}
	s2 = realloc(s2, (len1+1)*sizeof(char));
	s2[0] = len1;
	for(i = 1; i <= len1; ++i) {
		s2[i] = s1[i];
	}
	printf("Success!\n\n");
	return s2;
}

// returns the index in the first string where the second string exists, -1 otherwise
int substring(char* s1, char* s2) {
	int i, j, len1, len2;
	if(s1 == NULL) {
		printf("ERROR:\tCannot search in NULL string\n\n");
		return -1;
	}
	if(s2 == NULL) {
		printf("ERROR:\tSearching NULL string is undefined\n\n");
		return -1;
	}
	len1 = s1[0];
	len2 = s2[0];
	if (len2 > len1)
		return -1;
	for(i = 1; i <= len1; ++i) {
		for(j = 1; j <= len2; ++j) {
			if (s2[j] != s1[i+j-1])
				break;
		}
		if (j > len2)
			return i;
	}
	return -1;
}

void count_letters(char* str, int* count) {
	int i, len = str[0], temp;
	if(str == NULL) {
		printf("ERROR:\tNULL String\n\n");
		return;
	}
	for(i = 1; i <= len; ++i) {
		temp = str[i] - 'A';
		if (temp > 25)
			temp = str[i] - 'a';
		if (temp > 25)
			continue;
		++count[temp];
	}
}

char* case_switch(char* str, char c) {
	int temp, len;
	if(str == NULL) {
		printf("ERROR:\tNULL String\n\n");
		return NULL;
	}
	len = str[0];
	switch(c) {
		case 'l':
		case 'L':
				for(temp = 1; temp <= len; ++temp) {
					if(str[temp] >= 'A' && str[temp] <= 'Z')
						str[temp] += 'a' - 'A';
				}
				break;
		case 'u':
		case 'U':
				for(temp = 1; temp <= len; ++temp) {
					if(str[temp] >= 'a' && str[temp] <= 'z')
						str[temp] += 'A' - 'a';
				}
				break;
		default:
				printf("ERROR:\tInvalid choice of case\n\n");
				return NULL;
	}
	printf("Success!\n\n");
	return str;
}

char* replace_char(char* str, char ol, char nl) {
	int len, i;
	if(str == NULL) {
		printf("ERROR:\tNULL String\n\n");
		return NULL;
	}
	len = str[0];
	if(ol != nl) {
		for(i = 1; i <= len; ++i) {
			if(str[i] == ol)
				str[i] = nl;
		}
	}
	printf("Success!\n\n");
	return str;
}

int count_words(char* str) {
	int len, res, i;
	if (str == NULL)
		return 0;
	len = str[0];
	if(len > 0)
		res = 1;
	for(i = 1; i <= len; ++i)
		if (str[i] == ' ')
			++res;
	return res;
}

char* remove_char(char* str, char c) {
	int len, i, offset = 0;
	if(str == NULL) {
		printf("ERROR:\tNULL String\n\n");
		return NULL;
	}
	len = str[0];
	for(i = 1; i <= len; ++i) {
		if(str[i] == c)
			++offset;
		else
			str[i-offset] = str[i];
	}
	str[0] = str[0] - offset;
	str = realloc(str, str[0]+1);
	printf("Success!\n\n");
	return str;
}

char* revert(char* str) {
	int len, i;
	char temp;
	if(str == NULL) {
		printf("ERROR:\tNULL String\n\n");
		return NULL;
	}
	len = str[0];
	for(i = 1; i <= (len/2); ++i) {
		temp = str[i];
		str[i] = str[len-i+1];
		str[len-i+1] = temp;
	}
	printf("Success!\n\n");
	return str;
}

// controlling function
int main() {

	int choice, number = 0, temp, temp1, temp2, cont = 1, *count;
	char *s[MAX_NO];

	printf("String operations\n");
	printf(" 1. Create string\n");
	printf(" 2. Print all the stored strings\n");
	printf(" 3. Find Length of string\n");
	printf(" 4. Compare two strings\n");
	printf(" 5. Concatenate two strings\n");
	printf(" 6. Copy one string into another\n");
	printf(" 7. Search for a substring in a string\n");
	printf(" 8. Find frequency of letters in a string\n");
	printf(" 9. Convert the case of letters in a string\n");
	printf("10. Replace a letter with another one in a string\n");
	printf("11. Count no of words in a string\n");
	printf("12. Remove spaces from a string\n");
	printf("13. Revert a string\n");
	printf(" 0. Exit\n");
	printf("\n");

	while (cont) {

		printf("Choice: ");
		scanf("%d", &choice);
		getchar();

		switch(choice) {

			case 0:		cont = 0;
						break;

			case 1:		if(number >= MAX_NO) {
							printf("ERROR:\tCannot create more strings\n\n");
							break;
						}
						s[number++] = init();
						if(s[number-1] == NULL)
							--number;
						break;

			case 2:		for(temp2 = 0; temp2 < number; ++temp2) {
							printf("String %3d:\t", temp2+1);
							print(s[temp2]);
							printf("\n");
						}
						printf("\n");
						break;

			case 3:		printf("String number: ");
						scanf("%d", &temp);
						getchar();
						--temp;
						if (temp >= number) {
							printf("ERROR:\tString %d not created yet\n\n", temp);
							break;
						}
						printf("Length: %d\n\n", length(s[temp]));
						break;

			case 4:		printf("2 string numbers: ");
						scanf("%d %d", &temp, &temp1);
						getchar();
						--temp;
						--temp1;
						if (temp >= number) {
							printf("ERROR:\tString %d not created yet\n\n", temp);
							break;
						}
						if (temp1 >= number) {
							printf("ERROR:\tString %d not created yet\n\n", temp1);
							break;
						}
						temp2 = compare(s[temp], s[temp1]);
						if(temp2 == 1) {
							printf("String %d is greater\n\n", temp1+1);
						}
						else if(temp2 == 0) {
							printf("Strings %d and %d are equal\n\n", temp+1, temp1+1);
						}
						else if(temp2 == 2) {
							printf("ERROR:\t Could not compare the strings\n\n");
						}
						else {
							printf("String %d is greater\n\n", temp+1);
						}
						break;

			case 5:		printf("2 string numbers: ");
						scanf("%d %d", &temp, &temp1);
						getchar();
						--temp;
						--temp1;
						if (temp >= number) {
							printf("ERROR:\tString %d not created yet\n\n", temp);
							break;
						}
						if (temp1 >= number) {
							printf("ERROR:\tString %d not created yet\n\n", temp1);
							break;
						}
						s[number++] = concat(s[temp], s[temp1]);
						if(s[number-1] == NULL)
							--number;
						break;

			case 6:		printf("2 string numbers: ");
						scanf("%d %d", &temp, &temp1);
						getchar();
						--temp;
						--temp1;
						if (temp >= number) {
							printf("ERROR:\tString %d not created yet\n\n", temp);
							break;
						}
						if (temp1 >= number) {
							printf("ERROR:\tString %d not created yet\n\n", temp1);
							break;
						}
						copy(s[temp], s[temp1]);
						break;

			case 7:		printf("2 string numbers: ");
						scanf("%d %d", &temp, &temp1);
						getchar();
						--temp;
						--temp1;
						if (temp >= number) {
							printf("ERROR:\tString %d not created yet\n\n", temp);
							break;
						}
						if (temp1 >= number) {
							printf("ERROR:\tString %d not created yet\n\n", temp1);
							break;
						}
						temp2 = substring(s[temp], s[temp1]);
						if(temp2 == -1)
							printf("No search results found\n\n");
						else
							printf("Substring found at position %d\n\n", temp2);
						break;

			case 8:		printf("String number: ");
						scanf("%d", &temp);
						getchar();
						--temp;
						if (temp >= number) {
							printf("ERROR:\tString %d not created yet\n\n", temp);
							break;
						}
						count = malloc(26*sizeof(int));
						for(temp1 = 0; temp1 < 26; ++temp1)
							count[temp1] = 0;
						count_letters(s[temp], count);
						for(temp1 = 0; temp1 < 26; ++temp1)
							printf("%c: %2d\t\t", 'a'+temp1, count[temp1]);
						printf("\n\n");
						free(count);
						break;

			case 9:		printf("String number: ");
						scanf("%d", &temp);
						getchar();
						--temp;
						if (temp >= number) {
							printf("ERROR:\tString %d not created yet\n\n", temp);
							break;
						}
						printf("u for UPPERCASE, l for lowercase\nChoice: ");
						temp1 = getchar();
						getchar();
						case_switch(s[temp], (char)temp1);
						break;

			case 10:	printf("String number: ");
						scanf("%d", &temp);
						getchar();
						--temp;
						if (temp >= number) {
							printf("ERROR:\tString %d not created yet\n\n", temp);
							break;
						}
						printf("Original character: ");
						temp1 = getchar();
						getchar();
						printf("New character: ");
						temp2 = getchar();
						getchar();
						replace_char(s[temp], (char)temp1, (char)temp2);
						break;

			case 11:	printf("String number: ");
						scanf("%d", &temp);
						getchar();
						--temp;
						if (temp >= number) {
							printf("ERROR:\tString %d not created yet\n\n", temp);
							break;
						}
						temp1 = count_words(s[temp]);
						printf("Word count:  %d\n\n", temp1);
						break;

			case 12:	printf("String number: ");
						scanf("%d", &temp);
						getchar();
						--temp;
						if (temp >= number) {
							printf("ERROR:\tString %d not created yet\n\n", temp);
							break;
						}
						remove_char(s[temp], ' ');
						break;

			case 13:	printf("String number: ");
						scanf("%d", &temp);
						getchar();
						--temp;
						if (temp >= number) {
							printf("ERROR:\tString %d not created yet\n\n", temp);
							break;
						}
						revert(s[temp]);
						break;

			default:	printf("ERROR:\tWrong entry\n\n");
		}

	}
	for(temp2 = 0; temp2 < number; ++temp2) {
		free(s[temp2]);
	}
	return 0;
}
