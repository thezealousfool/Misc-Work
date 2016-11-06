#include <stdlib.h>
#include <stdio.h>

int main(int argc, char const *argv[])
{
	int n, m;
	char** mat;

	int temp, temp2;
	char* datap;

	// Input n, m. getchar() flushes the '\n' that stays in the buffer
	scanf("%d %d", &n, &m);
	getchar();

	// Allocate memory for elements as well as row headers
	mat = malloc(n * sizeof(char*) + (n * m) * sizeof(char));

	// Initialize the row headers
	datap = (char*)(mat + n);
	for(temp = 0; temp < n; ++temp, datap += m) {
		mat[temp] = datap;
	}

	// Taking input
	for(temp = 0; temp < n; ++temp) {
		for(temp2 = 0; temp2 < m; ++temp2) {
			mat[temp][temp2] = getchar();
		}
		getchar();
	}

	// Printing the result
	for(temp = 0; temp < n; ++temp) {
		for(temp2 = 0; temp2 < m; ++temp2) {
			printf("%c", mat[temp][temp2]);
		}
		printf("\n");;
	}

	return 0;
}