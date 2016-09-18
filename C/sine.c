#include <stdio.h>
#include <math.h>

int main() {
	static double PI = 3.1417;
	printf("x\tsin(x)\t\tcos(x)\t\ttan(x)\n");
	for (int i = 0; i<=360; i++) {
		float rad = PI/180 * i;
		printf("%d\t%f\t%f\t%f\n",i,sin(rad),cos(rad),tan(rad));
	}
	return 0;
}
