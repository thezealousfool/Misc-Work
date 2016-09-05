
#include <stdio.h>
#define MAX_LENGTH 101
#define WORD_MAX 51

int main(void)
{
	char string[MAX_LENGTH], word_search[WORD_MAX], word_replace[WORD_MAX];
	char new_string[MAX_LENGTH];
	char temp, choice;
	int index, count, search_len, replace_len, original_index, new_index;
	printf("1. Replace all vowels from string\n");
	printf("2. Replace all occurences of a word in string\n");
	printf("Enter choice: \n");
	scanf("%c", &choice);
	getchar();
	if (choice>'2' || choice<'1') {
		printf("Wrong entry!!\nAborting....\n");
		return 1;
	}
	printf("Enter string: ");
	scanf("%100[^\n]",string);
	getchar();
	if (choice=='1') {
		temp = string[0];
		index = 0;
		count = 0;
		while(temp!='\0') {
			if(temp=='a' || temp=='A' || temp=='e' || temp=='E' || temp=='i' || temp=='I' || temp=='o' || temp=='O' || temp=='u' || temp=='U') {
				++count;
			}
			else {
				new_string[index-count] = temp;
			}
			++index;
			temp = string[index];
		}
		new_string[index-count] = '\0';
	}
	else if (choice=='2') {
		printf("Enter word to be searched (max 50 characters): ");
		scanf("%50[^\n]",word_search);
		getchar();
		printf("Enter word to be replaced (max 50 characters): ");
		scanf("%50[^\n]",word_replace);
		getchar();
		search_len = 0;
		while (word_search[search_len]!='\0') ++search_len;
		replace_len = 0;
		while (word_replace[replace_len]!='\0') ++replace_len;
		original_index = 0;
		new_index = 0;
		while (string[original_index]!='\0') {
			index = 0;
			while ((index < search_len) && (string[original_index + index] == word_search[index]))
				++index;
			if (index == search_len) {
				index = 0;
				while (index < replace_len) {
					new_string[new_index + index] = word_replace[index];
					++index;
				}
				original_index += search_len;
				new_index += replace_len;
			}
			else {
				new_string[new_index] = string[original_index];
				++new_index;
				++original_index;
			}
			new_string[new_index] = '\0';
		}
	}
	printf("Result: %s\n", new_string);
	return 0;
}