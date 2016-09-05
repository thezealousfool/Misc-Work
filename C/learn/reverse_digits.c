#include <stdio.h>

int main() {
	int i, number, digit, array_number[100];
	printf("Enter number: ");
	scanf("%d",&number);
	if(number<1) {
		printf("Error!!\nEnter number greater than zero\nAborting!!\n");
		return 1;
	}
	for(i=0; number>0; ++i) {
		array_number[i] = number%10;
		number = number / 10;
	}
	array_number[i] = -1;
	printf("The number after reversing: ");
	for(i=0; array_number[i] != -1; ++i)
		printf("%d", array_number[i]);
	printf("\n");
	return 0;
}