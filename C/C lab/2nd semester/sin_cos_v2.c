#include <stdio.h>
#include <math.h>
#define width 70
#define PI 3.1415926
#define half_w width/2
int main() {
	int degree,loop_width,function1,function2;
	double radians;
	for(degree=0; degree<=360; degree+=5) {
		radians = PI * degree / 180.0;
		function1 = (int)(sin(radians)*half_w) + half_w;
		function2 = (int)(cos(radians)*half_w) + half_w;
		for(loop_width=0; loop_width<width; ++loop_width) {
			if(loop_width==function1) printf("*");
			else if (loop_width==function2) printf("#");
			else if (loop_width!=half_w) printf(" ");
			else printf("|");
		}
		printf("\n");
	}
	return 0;
}