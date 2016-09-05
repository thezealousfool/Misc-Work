#include <stdio.h>
#define max_length 100
int main() {
	char string[max_length];
	char ch;
	int index,count;
	scanf("%s",string);
	ch = string[0];
	index = 0;
	count = 0;
	while(ch!='\0') {
		if(ch=='a' || ch=='A' || ch=='e' || ch=='E' || ch=='i' || ch=='I' || ch=='o' || ch=='O' || ch=='u' || ch=='U')
			++count;
		++index;
		ch = string[index];
	}
	printf("%d\n", count);
	return 0;
}
