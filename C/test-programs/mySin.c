#include <stdio.h>
#define PI 3.1415926
int main(void) {
	int n,i;
	double radians,term,sum;
	scanf("%d",&n);
	radians = PI * n / 180.0;
	i=1;
	term = radians;
	sum = radians;
	while (term>=0.0001 || term<=-0.0001) {
		i = i+1;
		term = (-1*radians*radians*term)/((2*i-1)*(2*i-2));
		sum = sum+term;
	}
	printf("%f\n",sum);
	return 0;
}