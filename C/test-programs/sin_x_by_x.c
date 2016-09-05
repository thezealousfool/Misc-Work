#include <stdio.h>
#include <math.h>
int main(void) {
	int width,heigth,half_h,j,y,f;
	double i;
	width = 150;
	heigth = 40;
	half_h = (int)(heigth*3/4);
	for (j=0; j<heigth; j=j+1) {
		y = half_h-j;
		for(i=0; i<width*0.2; i=i+0.2) {
			if(i==0)
				f=half_h;
			else
				f=(int)(sin(i)/i*half_h);

			if(f==y) printf("*");
			else if(y!=0) printf(" ");
			else printf("-");			
		}
		printf("\n");
	}
	return 0;
}