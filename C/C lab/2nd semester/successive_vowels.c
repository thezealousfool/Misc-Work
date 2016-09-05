#include <stdio.h>
#define MAX_LENGTH 101

int is_vowel (char ch) {
	return ch=='a' || ch=='A' || ch =='e' || ch == 'E' || ch =='i' || ch == 'I' || ch =='o' || ch == 'O' || ch =='u' || ch == 'U' ; 
}

int main(void)
{
	int count;
	char text[MAX_LENGTH];
	int index;
	printf("Enter text: ");
	scanf("%100[^\n]", text);
	count = 0;
	index = 0;
	while (text[index+1]!='\0') {
		if (is_vowel(text[index]) && is_vowel(text[index+1]))
			++count;
		++index;
	}
	printf("No of two-vowels-in-succesions: %d\n", count);
	return 0;
}