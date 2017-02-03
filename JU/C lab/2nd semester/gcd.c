#include <stdio.h>
#include <math.h>
void factors (int number) {
	int no;
	int root;
	int divisor;
	no = number;
	root = sqrt(number);
	for (divisor=2; divisor<=root; divisor = divisor+1) {
		while (no%divisor==0 && no!=divisor) {
			printf("%d * ",divisor);
			no = no/divisor;
		}
	}
	if (no==number)
		printf("PRIME NUMBER\n");
	else
		printf("%d\n",no);
}

int main() {
	int number1,number2,dividend,divisor,temp;
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
	printf("GCD is %d\n",divisor);
	printf("LCM is %d\n",(number1*number2/divisor));
	printf("%d = ",number1);
	factors(number1);
	printf("%d = ",number2);
	factors(number2);
	return 0;
}