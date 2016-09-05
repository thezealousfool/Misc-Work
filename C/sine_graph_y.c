#include <stdio.h>
#include <math.h>

int main() {
	int i,j,k;
	float deg;
	for(i=0; i<=360; i+=5) {
		deg=sin(3.14159*i/180);
			j=(int)(deg*30) + 30;
			if(j>30) {
				for(k=30;k>=0;--k)
					printf(" ");
				printf("|");
				for(j=j-30;j>=0;--j)
					printf(" ");
				printf("*\n");
			}
			else if(j<30) {
				k=(int)(deg*30)+30;
				for(j=k; j>=0; --j){
					printf(" ");
				}
				printf("*");
				for(k=28-k;k>=0;--k){
					printf(" ");
				}
				printf("|\n");
			}
			else {
				for(j=30; j>=0; --j){
					printf(" ");
				}
				printf("*\n");
			}
		
		
	}
}