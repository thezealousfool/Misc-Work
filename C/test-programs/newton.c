#include <stdio.h>

int main(void) {
	double df,f,x;
	int n;
	scanf("%d",&n);
	x=1;
	f=x*x-n;
	df=2*x;
	while(f>=0.0001 || f<=-0.0001) {
		x=x-f/df;
		f=x*x-n;
		df=2*x;
	}
	printf("%f\n",x);
}