#include <stdio.h>

int main() {
	float number;
	int round, floor, ceil;
	printf("Enter number: ");
	scanf("%f", &number);
	floor = (int)number;
	if (floor == number)
		ceil = floor;
	else
		ceil = floor + 1;
	if (number-floor >= 0.5)
		round = ceil;
	else
		round = floor;
	printf("Floor: %d\nCeiling: %d\nRound: %d\n", floor, ceil, round);
	return 0;
}