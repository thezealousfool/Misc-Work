#include <stdio.h>

int check_sorted(int* arr, int size) {
	int diff, i;
	if(size < 0)
		return -2;
	if(size < 3)
		return 1;
	diff = arr[1] - arr[0];
	for(i = 2; i < size; ++i) {
		if ((arr[i] - arr[i-1])*diff < 0)
			return -2;
		else if (diff == 0)
			diff = arr[i] - arr[i-1];
	}
	if(diff == 0)
		return 0;
	if(diff > 0)
		return 1;
	return -1;
}

void print_s(int code) {
	if (code == -2)
		printf("Not sorted");
	else if (code == -1)
		printf("Sorted in Descending order");
	else if (code == 1)
		printf("Sorted in Ascending order");
	else if (code == 0)
		printf("Sorted in Constant order");
	else
		printf("ERROR!");
}

int main() {
	int a[] = {1,2,3,4,5,6,7,8,9,10};
	int b[] = {1,2,11,3,4,5,6,7,8,9,10};
	int c[] = {10,9,8,7,6,5,4,3,2,1};
	int d[] = {1,1,1,1,1};
	int e[] = {2,2,5,7,9,2,6};
	printf("1st array is "); print_s(check_sorted(a, 10)); printf("\n");
	printf("2nd array is "); print_s(check_sorted(b, 11)); printf("\n");
	printf("3rd array is "); print_s(check_sorted(c, 10)); printf("\n");
	printf("4th array is "); print_s(check_sorted(d, 5)); printf("\n");
	printf("5th array is "); print_s(check_sorted(e, 7)); printf("\n");
	return 0;
}
