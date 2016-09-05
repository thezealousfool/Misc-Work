#include <stdio.h>
#include <string.h>

int main() {
	char sentence[101], word_search[51], word_replace[51], *index;
	int length, count, i;
	for(i=0; i <50; ++i)
		word_replace[i] = '*';
	printf("Enter String (max 100 characters):\n");
	scanf("%100[^\n]",sentence);
	getchar();
	printf("Enter word to be searched (max 50 characters):\n");
	scanf("%50[^\n]",word_search);
	getchar();
	count = 0;
	length = strlen(word_search);
	index = strstr(sentence, word_search);
	while(index != NULL) {
		++count;
		strncpy(index, word_replace, length);
		index = strstr(sentence, word_search);
	}
	printf("The number of occurances is: %d\n", count);
	return 0;
}