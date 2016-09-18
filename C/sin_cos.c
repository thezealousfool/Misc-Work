#include <stdio.h>
#include <math.h>

int main() {
	int i,j;
	double sine,cosine;

	//for printing sin and cos from 0 to 45 degrees
	for (i=0; i<=45; i+=5) {
		sine = sin(3.14159*i/180);
		cosine = cos(3.14159*i/180);
		for(j = 30; j>0; --j) {
			printf(" ");
		}
		printf("|");
		for(j = (int)(sine*30); j>=0; --j) {
			printf(" ");
		}
		printf("*");
		for(j  = (int)(cosine*30) - (int)(sine*30); j>0; --j) {
			printf(" ");
		}
		printf("*\n");
	}

	//for printing sin and cos from 45 to 90 degrees
	for (i=50; i<=90; i+=5) {
		sine = sin(3.14159*i/180);
		cosine = cos(3.14159*i/180);
		for(j = 30; j>0; --j) {
			printf(" ");
		}
		printf("|");
		for(j = (int)(cosine*30); j>=0; --j) {
			printf(" ");
		}
		printf("*");
		for(j  = (int)(sine*30) - (int)(cosine*30); j>0; --j) {
			printf(" ");
		}
		printf("*\n");
	}

	//for printing sin and cos from 90 to 180 degrees
	for (i=95; i<=180; i+=5) {
		sine = sin(3.14159*i/180);
		cosine = cos(3.14159*i/180);
		for(j = (int)(cosine*30) + 30; j>0; --j) {
			printf(" ");
		}
		printf("*");
		for(j = -2 - (int)(cosine*30); j>=0; --j) {
			printf(" ");
		}
		printf("|");
		for(j = (int)(sine*30); j>=0; --j) {
			printf(" ");
		}
		printf("*\n");
	}

	//for printing sin and cos from 180 to 225 degrees
	for (i=185; i<=225; i+=5) {
		sine = sin(3.14159*i/180);
		cosine = cos(3.14159*i/180);
		for(j = (int)(cosine*30) + 30; j>0; --j) {
			printf(" ");
		}
		printf("*");
		for(j  = (int)(sine*30) - (int)(cosine*30); j>0; --j) {
			printf(" ");
		}
		printf("*");
		for(j = -3 - (int)(sine*30); j>=0; --j) {
			printf(" ");
		}
		printf("|\n");
	}

	//for printing sin and cos from 225 to 270 degrees
	for (i=230; i<270; i+=5) {
		sine = sin(3.14159*i/180);
		cosine = cos(3.14159*i/180);
		for(j = (int)(sine*30) + 30; j>0; --j) {
			printf(" ");
		}
		printf("*");
		for(j  = (int)(cosine*30) - (int)(sine*30); j>0; --j) {
			printf(" ");
		}
		printf("*");
		for(j = -3 - (int)(cosine*30); j>=0; --j) {
			printf(" ");
		}
		printf("|\n");
	}

	//for printing sin and cos from 270 to 360 degrees
	for (i=275; i<360; i+=5) {
		sine = sin(3.14159*i/180);
		cosine = cos(3.14159*i/180);
		for(j = (int)(sine*30) + 30; j>0; --j) {
			printf(" ");
		}
		printf("*");
		for(j = -2 - (int)(sine*30); j>=0; --j) {
			printf(" ");
		}
		printf("|");
		for(j = (int)(cosine*30); j>=0; --j) {
			printf(" ");
		}
		printf("*\n");
	}
}