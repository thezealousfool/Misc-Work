#include <stdio.h>

void to_hex(int n) {
	if(n<10)
			printf("%d",n);
		else if(n==10)
			printf("A");
		else if (n==11)
			printf("B");
		else if (n==12)
			printf("C");
		else if (n==13)
			printf("D");
		else if (n==14)
			printf("E")	;
		else if (n==15)
			printf("F");
}

void print_hex(int n) {
	if(n<16)
		to_hex(n);
	else {
		print_hex(n/16);
		to_hex(n%16);
	}
}

int main() {
	float no;
	int before_decimal;
	float after_decimal;
	int remain;
	scanf("%f",&no);
	before_decimal = (int)no;
	after_decimal = no - before_decimal;
	print_hex(before_decimal);
	printf(".");
	while (after_decimal>0.00001) {
		after_decimal *= 16;
		remain = (int)(after_decimal);
		to_hex(remain);
		after_decimal -= remain;
	}
	printf("\n");
	return 0;
}