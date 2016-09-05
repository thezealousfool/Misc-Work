#include <stdio.h>
#include <stdlib.h>

void product_matrices (int** matrix1, int m1, int n1, int** matrix2, int m2, int n2, int** matrix3) {
    int row_loop, column_loop, inner_loop;
    
    if (n1 != m2) {
        printf("Error!! These matrices cannot be multiplied\n");
    }    
    
    for (row_loop=0; row_loop<m1; ++row_loop) {
        for (column_loop=0; column_loop<n2; ++column_loop) {
            for (inner_loop=0; inner_loop<n1; ++inner_loop) {
                matrix3[row_loop][column_loop] += matrix1[row_loop][inner_loop]*matrix2[inner_loop][column_loop];
            }
        }
    }
}

int main(void) {
    int **m1, **m2, **m3, loop1, loop2;
    int a1,b1,a2,b2;
    printf("Enter the size of first matrix (2 integers):\n");
    scanf("%d %d", &a1, &b1);
    printf("Enter the size of second matrix (2 integers):\n");
    scanf("%d %d", &a2, &b2);
    m1 = malloc(a1*sizeof(int*));
    for (loop1 = 0; loop1<a1; ++loop1)
        m1[loop1] = malloc(b1*sizeof(int));
    m2 = malloc(a2*sizeof(int*));
    for (loop1 = 0; loop1<a2; ++loop1)
        m2[loop1] = malloc(b2*sizeof(int));
    printf("Enter first matrix values\n");
    for (loop1=0; loop1<a1; ++loop1) {
        for (loop2=0; loop2<b1; ++loop2) {
            // printf("Enter value at row %d column %d: ", loop1+1, loop2+1);
            scanf("%d", &m1[loop1][loop2]);
        }
    }
    printf("Enter second matrix values\n");
    for (loop1=0; loop1<a2; ++loop1) {
        for (loop2=0; loop2<b2; ++loop2) {
            // printf("Enter value at row %d column %d: ", loop1+1, loop2+1);
            scanf("%d", &m2[loop1][loop2]);
        }
    }
    m3 = malloc(a1*sizeof(int*));
    for (loop1=0; loop1<a1; ++loop1) {
        m3[loop1] = malloc(b2*sizeof(int));
    }
    for (loop1=0; loop1<a1; ++loop1) {
        for (loop2=0; loop2<b2; ++loop2) {
                m3[loop1][loop2] = 0;
        }
    }
    product_matrices (m1, a1, b1, m2, a2, b2, m3);
    printf("The product of the two matrices is:\n");
    for (loop1=0; loop1<a1; ++loop1) {
        for (loop2=0; loop2<b2; ++loop2) {
            printf("%d ", m3[loop1][loop2]);
        }
        printf("\n");
    }
}