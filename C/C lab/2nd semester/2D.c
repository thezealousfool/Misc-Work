#include <stdio.h>
#include <stdlib.h>

struct coordinates {
	int x, y;
};

int main() {
	int N,i;
	struct coordinates* points;
	int min_x,max_x,min_y,max_y;
	scanf("%d",&N);
	srand(time(NULL));
	points = malloc(N*sizeof(struct coordinates));
	for(i=0; i<N; i=i+1) {
		(points+i)->x=rand()%100;
		(points+i)->y=rand()%100;
	}
	min_x = points->x;
	min_y = points->y;
	max_x = points->x;
	max_y = points->y;
	printf("\nNumber of points: %d\nPoints are:\n",N);
	for(i=0; i<N; i=i+1) {
		printf("(%d,%d)\n",(points+i)->x,(points+i)->y);
	}
	printf("\n\n");
	for(i=1; i<N; i=i+1) {
		if(((points+i)->x) < min_x) {
			min_x = (points+i)->x;
			min_y = (points+i)->y;
		}
		else if((points+i)->x == min_x) {
			if ((points+i)->y < min_y)
				min_y = (points+i)->y;
		}
		if (((points+i)->x) > max_x) {
			max_x = (points+i)->x;
			max_y = (points+i)->y;
		}
		else if ((points+i)->x == max_x) {
			if((points+i)->y > max_y)
				max_y = (points+i)->y;
		}
	}
	printf("Leftmost points:\nx = %d\t\ty = %d\n",min_x,min_y);
	printf("\nRightmost points:\nx = %d\t\ty = %d\n",max_x,max_y);
	return 0;
}
