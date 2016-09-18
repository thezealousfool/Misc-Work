#include <stdio.h>
#include <math.h>
#define PI 3.1415926
#define g 9.81
int main() {
	float o,u;
	float deg,range,max_height;
	scanf("%f",&u);
	scanf("%f",&deg);
	o = PI*deg/180.0;
	range = (u*u*sin(2*o)/g);
	max_height = (u*u*sin(o)*sin(o)/(2*g));
	printf("u:%f\ndegree:%f\nradian:%f\nrange:%f\nheight:%f\n",u,deg,o,range,max_height);
}