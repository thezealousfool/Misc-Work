#include <stdio.h>
#include <unistd.h>
#define width 149
#define height 39
int main() {
	int i,j,k;
	char screen[height][width];
	for(i=0; i<height; ++i) {
		for(j=0; j<width; ++j) {
			screen[i][j]=' ';
		}
	}
	for(i=0; i<height; ++i) {
		for(j=0; j<width; ++j)
			screen[i][j]=' ';
	}
	for(k=height-1; k>=0; --k) {
		screen[k][0]='*';
		for(i=0; i<height; ++i) {
			for(j=0; j<width; ++j) {
				printf("%c",screen[i][j]);
			}
			printf("\n");
		}
		screen[k][0]=' ';
		sleep(1);
	}
	return 0;
}