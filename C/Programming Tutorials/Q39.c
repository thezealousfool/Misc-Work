#include <stdio.h>

void part_a (int terms) {
    int term, to_be_added;
    term = 1; to_be_added = 2;
    while (terms--) {
        printf("%d ", term);
        term += to_be_added;
        ++to_be_added;
    }
    printf("\n");
}

void part_b (int terms) {
    void fib(int a, int b, int no_terms) {
        if (no_terms <= 0)
            return;
        printf("%d ", b);
        fib (b, a+b, no_terms-1);
    };
    if (terms > 0)
        printf("1 ");
    fib(1, 1, terms-1);
    printf("\n");
}

void part_c (int terms) {
    int term, to_be_added;
    term = 2; to_be_added = 3;
    while (terms--) {
        printf("%d ", term);
        term += to_be_added;
        to_be_added += 2;
    }
    printf("\n");
}

void part_d (int terms) {
    int term, to_be_added, present_max;
    if (terms > 0)
        printf("1 ");
    --terms;
    term = 2; to_be_added = 1; present_max = 2;
    while (terms--) {
        printf("%d ", term);
        if (term == present_max) {
            to_be_added = -1;
        }
        else if (term == 1) {
            to_be_added = 1;
            ++present_max;
        }
        term += to_be_added;
    }
}

int main() {
    int terms;
    printf("Enter no of terms of SERIES 1 to print: ");
    scanf("%d", &terms);
    part_a(terms);
    printf("Enter no of terms of SERIES 2 to print: ");
    scanf("%d", &terms);
    part_b(terms);
    printf("Enter no of terms of SERIES 3 to print: ");
    scanf("%d", &terms);
    part_c(terms);
    printf("Enter no of terms of SERIES 4 to print: ");
    scanf("%d", &terms);
    part_d(terms);
}