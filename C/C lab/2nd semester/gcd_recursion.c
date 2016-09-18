#include <stdio.h>

int GCD (int divisor, int dividend) {
	if (dividend%divisor!=0)
		divisor = GCD(dividend%divisor, divisor);
	return divisor;
}

int main() {
	int number1,number2,dividend,divisor,temp;
	printf("Finding GCD using iteration\n");
	printf("Enter 2 numbers: ");
	scanf("%d %d",&number1,&number2);
	if(number1<number2) {
		divisor=number1;
		dividend=number2;
	}
	else {
		dividend=number1;
		divisor=number2;
	}
	while (dividend%divisor!=0) {
		temp=divisor;
		divisor=dividend%divisor;
		dividend=temp;
	}
	printf("GCD is %d\n\n",divisor);
	printf("Finding GCD using recursion\n");
	printf("Enter 2 numbers: ");
	scanf("%d %d",&number1,&number2);
	if(number1<number2) {
		divisor=number1;
		dividend=number2;
	}
	else {
		dividend=number1;
		divisor=number2;
	}
	printf("%d\n", GCD(divisor, dividend));
}