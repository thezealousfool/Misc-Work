#include <stdio.h>
#include <math.h>

int main() {
	long long int number1,number2,dividend,divisor,temp;
	int T;
	scanf("%d",&T);
	while(T--) {
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
		printf("%d %d\n",divisor,(number1*number2/divisor));
	}
	return 0;
}