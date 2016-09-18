
#include <stdio.h>
#include <math.h>

int main() {
	int loop_1,i;
	float term,my_sine,sine_value;
	printf("Angle\tsin(x)\t\tMy sin(x)\tMy sin(x) - sin(x)\n");
	for(loop_1=0; loop_1<=360; loop_1 = loop_1 + 5) {
		sine_value = loop_1 * 3.1416 / 180;
		i=2;
		my_sine = sine_value;
		term = sine_value;
		while (term>=0.000001 || term<=-0.000001) {
			term = term * (-1*sine_value*sine_value) / ((2*i - 1)*(2*i - 2));
			i=i+1;
			my_sine = my_sine + term;
		};
		printf("%d\t%9.6f\t%9.6f\t%9.6f\n",loop_1,sin(sine_value),my_sine,my_sine-sin(sine_value));
	};
	return 0;
}

