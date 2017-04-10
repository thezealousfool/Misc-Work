#include <stdio.h>
#include <stdlib.h>

// merge a1's first n1 elements with a2's first n2 elements ordered as o into res
// if oreder is ascending then o is positive else negative
int* merge(int* a1, int n1, int* a2, int n2, int o, int* res) {
	int i = 0, j = 0, k = 0, flag = 0;
	while(i < n1 && j < n2) {
		if(*(a1+i) > *(a2+j))
				flag = 1;
		else
				flag = 0;

		if((o > 0) == flag) {
			*(res+k) = *(a2+j);
			++j;
		}
		else {
			*(res+k) = *(a1+i);
			++i;
		}
		++k;
	}
	if(i == n1 && j == n2)
		return res;
	if(i == n1) {
		while(j < n2) {
			*(res+k) = *(a2+j);
			++j;
			++k;
		}
		return res;
	}
	if(j == n2) {
		while(i < n1) {
			*(res+k) = *(a1+i);
			++i;
			++k;
		}
		return res;
	}
	return res;
}


int main() {
	int a[] = {1,5,9,22,34,55};
	int b[] = {3,6,7,11,17,29,47};
	int c[13], i;
	merge(a, 6, b, 7, 5, c);
	for(i = 0; i < 13; ++i)
		printf("%2d  ", c[i]);
	printf("\n");
	return 0;
}
