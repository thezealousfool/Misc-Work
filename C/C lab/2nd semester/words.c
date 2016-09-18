/*input
Ghosh Ghosh
Ghosh
Roy
*/
#include <stdio.h>
#include <string.h>

int is_word(char *sentence, int index, char *word) {
	int word_index = 0;
	while(word[word_index] != '\0') {
		if(sentence[index+word_index]!=word[word_index])
			return 0;
		++word_index;
	}
	return 1;
}

void replace_word(char *sentence, int index, int len, char *word) {
	if(len==strlen(word)) {
		for(int word_index=0; word_index<len; ++word_index)
			sentence[index+word_index] = word[word_index];
		return;
	}
}

int main() {
	char sentence[101], word_search[51], word_replace[51];
	printf("Enter String (max 100 characters):\n");
	scanf("%100[^\n]",sentence);
	getchar();
	printf("Enter word to be searched (max 50 characters):\n");
	scanf("%50[^\n]",word_search);
	getchar();
	printf("Enter word to replace searched word (%d characters):\n", strlen(word_search));
	scanf("%50[^\n]",word_replace);
	getchar();
	for(int index=0; sentence[index]!='\0'; ++index) {
		if(is_word(sentence, index, word_search))
			replace_word(sentence, index, strlen(word_search), word_replace);
	}
	printf("Sentence after replacing \"%s\" with \"%s\":\n%s\n", word_search, word_replace, sentence);
}