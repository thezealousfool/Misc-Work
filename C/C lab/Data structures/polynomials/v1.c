#include <stdio.h>
#define MAX_POLY 50
#define MAX_TERM 500

typedef struct {
	float coeff, exp;
} term;

void disp_term_pool (term *term_pool, int end) {
	int pres;
	printf("end: %d\n", end);
	for (pres = 0; pres < end; ++pres) {
		printf("(%f,%f) ", term_pool[pres].coeff, term_pool[pres].exp);
	}
	printf("\n");
}

void disp_poly_start (int *poly_start, int no_poly) {
	int pres;
	printf("no_poly: %d\n", no_poly);
	for (pres = 0; pres <= no_poly; ++pres) {
		printf("%d ", poly_start[pres]);
	}
	printf("\n");
}

int init_poly (int *poly_start, int *poly_index) {

	if (*poly_index >= MAX_POLY) {
		return 1;
	}

	printf("init_poly::poly_index: %d\n", *poly_index);
	poly_start[(*poly_index) + 1] = poly_start[(*poly_index)];
	++(*poly_index);
	disp_poly_start(poly_start, *poly_index);
	return 0;
}

int add_term (term *term_pool, int *end, float coeff, float exp) {

	if ((*end) == (MAX_TERM - 1))
		return 2;

	term_pool[*end].coeff = coeff;
	term_pool[*end].exp = exp;
	++(*end);
	return 0;
}

int inp_poly (term *term_pool, int *poly_start, int *poly_index, int *end) {

	int err_code = 0, no_term;
	float coeff, exp;

	err_code = init_poly(poly_start, poly_index);
	if (err_code)
		return err_code;

	printf("Enter no of terms:	");
	scanf("%d", &no_term);
	
	if ((*end) + no_term > MAX_TERM)
		return 2;
	printf("inp_poly::poly_index: %d\n", *poly_index);

	while (no_term--) {
		printf("Enter coefficient:		");
		scanf("%f", &coeff);
		printf("Enter exponent:			");
		scanf("%f", &exp);

		add_term(term_pool, end, coeff, exp);
		++poly_start[(*poly_index)];
	}
	
	return 0;
}

int disp_poly (term *term_pool, int *poly_start, int no_poly, int poly_index) {
	int pres;
	if (poly_index >= no_poly)
		return 1;
	for (pres = poly_start[poly_index]; pres < poly_start[poly_index + 1]; ++pres) {
		printf("%f*x^%f", term_pool[pres].coeff, term_pool[pres].exp);
		if (pres == poly_start[poly_index + 1] - 1)
			printf("\n");
		else
			printf ("  +  ");
	}
	return 0;
}

void disp_all_poly (term *term_pool, int *poly_start, int no_poly) {
	int pres;
	for (pres = 0; pres < no_poly; ++pres) {
		disp_poly(term_pool, poly_start, no_poly, pres);
	}
}

int disp_err (int err_code) {
	if (err_code == 1) {
		printf("Maximum no of polynomials reached!\nAborting!\n");
		return 1;
	}
	else {
		printf("Maximum no of terms reached!\nAborting!\n");
		return 2;
	}
}

int main() {
	int no_poly = 0;
	term term_pool[MAX_TERM];
	int poly_start[MAX_POLY + 1];
	int end = 0;
	poly_start[0] = 0;
	int err_code = 0;
	err_code = inp_poly(term_pool, poly_start, &no_poly, &end);
	if(err_code) {
		return disp_err(err_code);
	}
	disp_all_poly(term_pool, poly_start, no_poly);
	disp_term_pool(term_pool, end);
	disp_poly_start(poly_start, no_poly);
	err_code = inp_poly(term_pool, poly_start, &no_poly, &end);
	if(err_code) {
		return disp_err(err_code);
	}
	disp_all_poly(term_pool, poly_start, no_poly);
	disp_term_pool(term_pool, end);
	disp_poly_start(poly_start, no_poly);
	return 0;
}
