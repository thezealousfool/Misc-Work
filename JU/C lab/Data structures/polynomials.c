#include <stdio.h>
#define MAX_LEN 200
#define MAX_NO_POLY 30

typedef struct {
	double coeff, exp;
} elem;


void disp_poly (elem *poly_pool, int *poly_start, int no_poly, int pool_end, int index);
void disp_all (elem *poly_pool, int *poly_start, int no_poly, int end);
int init_poly (int *poly_start, int *no_poly, int end);
int new_elem (elem *poly_pool, int *end, double coeff, double exp);
int input_poly (elem *poly_pool, int *poly_start, int *no_poly, int *end);
int add_subs_poly (elem *poly_pool, int *poly_start, int *no_poly, int *end, int poly1, int poly2, int sign);
int add_poly (elem *poly_pool, int *poly_start, int *no_poly, int *end, int poly1, int poly2);
int subs_poly (elem *poly_pool, int *poly_start, int *no_poly, int *end, int poly1, int poly2);

int main() {
	elem poly_pool[MAX_LEN];
	int poly_start[MAX_NO_POLY];
	int no_poly = 0;;
	int end = 0;
	int choice = 6;
	int temp1, temp2;
	while (1) {
		printf("Polynomial operations:\n");
		printf("1. Insert new polynomial\n");
		printf("2. Add two polynomials\n");
		printf("3. Substract two polynomials\n");
		printf("4. Print a polynomial\n");
		printf("5. Print all polynomials\n");
		printf("6. Exit\n");
		printf("\nEnter choice: ");
		scanf("%d", &choice);
		switch (choice) {
			case 1:	if(input_poly(poly_pool, poly_start, &no_poly, &end)) {
						printf("Unable to insert new polynomial\n\n");
					}
					else {
						printf("Polynomial successfully inserted at number: %d\n\n", no_poly);
					}
					break;
			case 2: printf("Adding two polynomials\n");
					printf("Enter the numbers of the two polynomials to be added: ");
					scanf("%d %d", &temp1, &temp2);
					if (add_poly(poly_pool, poly_start, &no_poly, &end, temp1-1, temp2-1)) {
						printf("Unable to add the polynomials\n\n");
					}
					else {
						printf("Polynomials successfully added at number: %d\n\n", no_poly);
					}
					break;
			case 3: printf("Substracting two polynomials\n");
					printf("Enter the numbers of the two polynomials to be substracted: ");
					scanf("%d %d", &temp1, &temp2);
					if (add_poly(poly_pool, poly_start, &no_poly, &end, temp1-1, temp2-1)) {
						printf("Unable to substract the polynomials\n\n");
					}
					else {
						printf("Polynomials successfully substracted at number: %d\n\n", no_poly);
					}
					break;
			case 4:	printf("Printing polynomial\n");
					printf("Enter number of polynomial to be printed: ");
					scanf("%d", &temp1);
					disp_poly(poly_pool, poly_start, no_poly, end, temp1-1);
					break;
			case 5:	printf("Printing all polynomials\n");
					disp_all(poly_pool, poly_start, no_poly, end);
					break;
			case 6:	
			default:return 0;
		}
	}
}

void disp_poly (elem *poly_pool, int *poly_start, int no_poly, int pool_end, int index) {
	if (index >= no_poly) {
		return;
	}
	int start = poly_start[index], end;
	if (index == no_poly - 1)
		end = pool_end;
	else
		end = poly_start[index + 1];
	while (start != end) {
		printf("%lf x^%lf", poly_pool[start].coeff, poly_pool[start].exp);
		++start;
		if (start != end)
			printf("   +   ");
	}
	printf("\n");
}

void disp_all (elem *poly_pool, int *poly_start, int no_poly, int end) {
	int temp = 0;
	for (temp = 0; temp < no_poly; ++temp) {
		printf("Polynomial %d:\n", temp+1);
		disp_poly(poly_pool, poly_start, no_poly, end, temp);
	}
}

int init_poly (int *poly_start, int *no_poly, int end) {
	if (*no_poly >= MAX_NO_POLY)
		return 1;
	poly_start[*no_poly] = end;
	++(*no_poly);
	return 0;
}

int new_elem (elem *poly_pool, int *end, double coeff, double exp) {
	if (*end >= MAX_LEN) {
		return 1;
	}
	poly_pool[*end].coeff = coeff;
	poly_pool[*end].exp = exp;
	++(*end);
	return 0;
}

int input_poly (elem *poly_pool, int *poly_start, int *no_poly, int *end) {
	int no = 0, temp = 0, temp_end = *end;
	double exp = 0.0, coeff = 0.0;
	if(init_poly(poly_start, no_poly, *end)) {
		return 1;
	}
	printf("Enter no of elements: ");
	scanf("%d", &no);
	for (temp = 0; temp < no; ++temp) {
		printf("Enter coefficient: ");
		scanf("%lf", &coeff);
		printf("Enter exponent: ");
		scanf("%lf", &exp);
		if (new_elem(poly_pool, &temp_end, coeff, exp)) {
			printf("Error! Overflow! Aborting!\n");
			--(*no_poly);
			return 1;
		}
	}
	*end = temp_end;
	return 0;
}

int add_subs_poly (elem *poly_pool, int *poly_start, int *no_poly, int *end, int poly1, int poly2, int sign) {
	if (poly1 >= *no_poly || poly2 >= *no_poly)
		return 1;
	if(init_poly(poly_start, no_poly, *end))
		return 1;
	int poly1_index = poly_start[poly1];
	int poly2_index = poly_start[poly2];
	int poly1_end, poly2_end;
	int temp_end = *end;
	if (poly1 == *no_poly - 1)
		poly1_end = *end;
	else
		poly1_end = poly_start[poly1 + 1];
	if (poly2 == *no_poly - 1)
		poly2_end = *end;
	else
		poly2_end = poly_start[poly2 + 1];
	while (poly1_index < poly1_end || poly2_index < poly2_end) {
		if (poly2_index >= poly2_end || poly_pool[poly1_index].exp < poly_pool[poly2_index].exp) {
			if(new_elem(poly_pool, &temp_end, poly_pool[poly1_index].coeff, poly_pool[poly1_index].exp)) {
				--(*no_poly);
				return 1;
			}
			++poly1_index;
		}
		else if (poly1_index >= poly1_end || poly_pool[poly1_index].exp > poly_pool[poly2_index].exp) {
			if(new_elem(poly_pool, &temp_end, poly_pool[poly2_index].coeff, poly_pool[poly2_index].exp)) {
				--(*no_poly);
				return 1;
			}
			++poly2_index;
		}
		else {
			if(new_elem(poly_pool, &temp_end, poly_pool[poly2_index].coeff + sign * poly_pool[poly1_index].coeff, poly_pool[poly2_index].exp)) {
				--(*no_poly);
				return 1;
			}
			++poly1_index; ++poly2_index;
		}
	}
	*end = temp_end;
	return 0;
}

int add_poly (elem *poly_pool, int *poly_start, int *no_poly, int *end, int poly1, int poly2) {
	return add_subs_poly(poly_pool, poly_start, no_poly, end, poly1, poly2, 1);
}

int subs_poly (elem *poly_pool, int *poly_start, int *no_poly, int *end, int poly1, int poly2) {
	return add_subs_poly(poly_pool, poly_start, no_poly, end, poly1, poly2, -1);
}
