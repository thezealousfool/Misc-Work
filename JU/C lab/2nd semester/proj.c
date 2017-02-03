#include <stdio.h>
#include <math.h>
#define g 9.81
#define PI 3.1416
#define w 150
#define h 40
float u,o;
int return_y (int x) {
	float t = x/(u*cos(o));
	return u*sin(o)*t - 0.5*g*t*t;
}
int main() {
	int i,j,k,y;
	int angle,range;
	char screen[h+1][w+1];
	printf("Enter initial speed (m/s): ");
	scanf("%f",&u);
	printf("Enter angle (degrees): ");
	scanf("%d",&angle);
	o = PI*angle/180.0;
	for(i=0; i<h; ++i) {
		for(j=0; j<w; ++j)
			screen[i][j]=' ';
	}
	for (i=0; ;++i) {
		y = return_y(i);
		if(y<0 || i>=w)
			break;
		if(y>=h)
			continue;
		screen[h-y-1][i] = '*';
		for(k=0; k<h; ++k) {
			for(j=0; j<w; ++j)
				printf("%c",screen[k][j]);
			printf("\n");
		}
		//	screen[h-y-1][i] = ' ';
		for(k=0; k<10000000; ++k);
	}
	
	return 0;
}