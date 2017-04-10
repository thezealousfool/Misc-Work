#include <stdio.h>
#include <stdlib.h>
#define LEN 100

typedef struct{
    double value;
    unsigned int r, c;
} matrix;

void SortSparseMatrix(matrix array[LEN]){
    int count, j, cond;
    matrix t;
    
    for(count = 2; count < (array[0].value) + 1; ++count) {
        j = count-1;
        t = array[count];
        cond = array[j].r > t.r || (array[j].r == t.r && array[j].c > t.c);
        
        while(cond && j > 0) {
            array[j+1] = array[j];
            --j;
            cond = (array[j].r > t.r) || (array[j].r == t.r && array[j].c > t.c);
        }

        array[j+1] = t;
    }
}

void printSparseMatrix(matrix array[LEN]){
    int count, i, j;
    printf("\n");
    double M[100][100];

    for(i = 0; i < 100; ++i) {
        for(j = 0; j < 100; ++j) {
            M[i][j] = 0;
        }
    }
    
    for(count = 1; count <= array[0].value; ++count)
        M[array[count].r][array[count].c] = array[count].value;

    for(i = 1; i <= array[0].r; i++){
        for(j = 1; j <= array[0].c; j++)
            printf("%.4lf   ",M[i][j]);
        printf("\n");
    }   
    printf("\n\n");
}

void inputSparseMatrix(matrix array[LEN]){
    int i,j;
    double input;
    
    printf("\nEnter the Dimensions of the Matrix: ");
    scanf("%d %d", &(array[0].r), &(array[0].c));
    
    array[0].value = 0;
    printf("Enter the Matrix: \n");
    for(i = 1; i <= (array[0].r); ++i) {
        for(j = 1; j <= (array[0].c); ++j){
            scanf("%lf", &input);

            if(input <= -0.001 || input >= 0.001){
                ++(array[0].value);
                array[(int)(array[0].value)].r = i;
                array[(int)(array[0].value)].c = j;
                array[(int)(array[0].value)].value = input;
            }       
        }
    }

    SortSparseMatrix(array);
    printSparseMatrix(array);
}

void addSparse(matrix array1[LEN], matrix array2[LEN], matrix array[LEN]) {
    int count, j, f;

    if((array1[0].c) != (array2[0].c) || (array1[0].r) != (array2[0].r)) {
        printf("\nInvalid Dimensions of two matrices.");
        return;
    }

    array[0].c = array1[0].c;
    array[0].r = array1[0].r;
    array[0].value = 0;
    
    for(count = 1; count <= array1[0].value; ++count) {
        ++(array[0].value);
        array[count].r = array1[count].r;
        array[count].c = array1[count].c;
        array[count].value = array1[count].value;
        for(j = 1; j <= array2[0].value; ++j)
            if(array2[j].r == array1[count].r && array2[j].c == array1[count].c)
                array[count].value += array2[j].value;
    }
    
    for(count = 1; count <= array2[0].value; ++count) {
        f = 1;
        for(j = 1; j <= array1[0].value; ++j)
            if(array2[count].r == array1[j].r && array2[count].c == array1[j].c) {
                f = 0;
                break;
            }
        
        if(f) {
            ++(array[0].value);
            array[(int)array[0].value].r = array2[count].r;
            array[(int)array[0].value].c = array2[count].c;
            array[(int)array[0].value].value = array2[count].value;
        }
    }

    SortSparseMatrix(array);
    printf("\nSum:\n");
    printSparseMatrix(array);
}

void Multiply(matrix array1[LEN], matrix array2[LEN], matrix array[LEN]){
    int count, j, k, l, cond;
    double sum;

    if(array1[0].c != array2[0].r) {
        printf("\nMatrices are not multiplicable\n");
        return;
    }

    array[0].r = array1[0].r;
    array[0].c = array2[0].c;
    array[0].value = 0;
    for(count = 1; count <= array1[0].r; ++count)
        for(j = 1; j <= array2[0].c; ++j){
            sum = 0;

            for(k = 1; k <= array1[0].value; ++k)
                for(l = 1; l <= array2[0].value; ++l){
                    cond = (array1[k].r == count) && (array2[l].c == j) && (array1[k].c == array2[l].r);
                    if(cond)
                       sum += array1[k].value * array2[l].value;
               }

            if(sum) {
                ++(array[0].value);
                array[(int)array[0].value].r = count;
                array[(int)array[0].value].c = j;
                array[(int)array[0].value].value = sum;
            }
        }   

    SortSparseMatrix(array);  
    printf("\nSum:\n");
    printSparseMatrix(array);
}
void Multiply_Sparse(matrix array[LEN], double scalar, matrix array1[LEN]){
    int count;
    
    array1[0].c = array[0].c;
    array1[0].r = array[0].r;
    array1[0].value = array[0].value;

    if(scalar == 0){
        array1[0].value = 0;
        return;
    }

    for(count = 1; count <= array[0].value; ++count) {
        array1[count].r = array[count].r;
        array1[count].c = array[count].c;
        array1[count].value = array[count].value * scalar;
    }

    printf("\nProduct:\n");
    printSparseMatrix(array1);
}

void transSparse(matrix array[LEN], matrix array1[LEN]){
    int count, t;

    for(count = 0; count < array[0].value + 1; ++count)
        array1[count] = array[count];

    for(count = 0; count < array[0].value + 1; ++count){
        t = array1[count].r;
        array1[count].r = array1[count].c;
        array1[count].c = t;
    }
    
    SortSparseMatrix(array1);
    printf("Transpose: \n");
    printSparseMatrix(array1);
}

double determinant(matrix array[LEN]) {
    int j, i, m, c, k;
    double det = 0;
    matrix temp[LEN];

    if(array[0].value == 0)
        return 0;
    
    if(array[0].r == 1 && (int)array[0].value == 1)
        return array[1].value;
    else if(array[0].r == 1 && (int)array[0].value == 0)
        return 0;
    
    j = array[1].r;

    if(j > 1)
        return 0;
    
    for(i = 1; i < array[0].value; ++i)
    {
        if(array[i].r > j)
            break;
        temp[0].r = temp[0].c = array[0].r - 1;
        temp[0].value = 0;

        for(c = i+1; c <= array[0].value; ++c)
            if(array[c].r > array[i].r && array[c].c != array[i].c)
            {
                ++(temp[0].value);
                temp[(int)(temp[0].value)].value = array[c].value;
                temp[(int)(temp[0].value)].r = array[c].r-1;

                if(array[i].c > array[c].c)
                    temp[(int)(temp[0].value)].c = array[c].c;
                else
                    temp[(int)(temp[0].value)].c = array[c].c-1;
            }

        if(array[i].c%2 == 0)
            m = -1;
        else
            m = 1;
    
        SortSparseMatrix(temp);
        det = det + m*determinant(temp)*(array[i].value);
    }

    return det;
}

void inverse(matrix array[LEN], matrix result2[LEN]){
    int i, j, count;
    double temp1, m;
    matrix temp[LEN], result1[LEN], result[LEN];
    
    if(array[0].r != array[0].c) {
        printf("Matrix is not invertible\n");
        return;
    }

    if(determinant(array) == 0) {
        printf("Matrix is not invertible\n");
        return;
    }

    result[0].r = array[0].r;
    result[0].c = array[0].c;
    result[0].value = 0;
    
    for(i = 1; i <= array[0].r; i++)
        for(j = 1; j <= array[0].c; j++){
            temp[0].r = array[0].r-1;
            temp[0].c = array[0].c-1;
            temp[0].value = 0;

            for(count = 1;count <= array[0].value; count++)    
                if(array[count].r != i && array[count].c != j) {
                    ++(temp[0].value);

                    if(array[count].c < j)
                        temp[(int)(temp[0].value)].c = array[count].c;
                    else
                        temp[(int)(temp[0].value)].c = array[count].c-1;

                    if(array[count].r < i)
                        temp[(int)(temp[0].value)].r = array[count].r;
                    else
                        temp[(int)(temp[0].value)].r = array[count].r-1;

                    temp[(int)(temp[0].value)].value = array[count].value;
                }

            SortSparseMatrix(temp);
            temp1 = determinant(temp);

            if(temp1 <= -0.001 || temp1 >= 0.001) {
                ++(result[0].value);
                result[(int)(result[0].value)].r = i;
                result[(int)(result[0].value)].c = j;
                
                if((i+j)%2 == 0)
                    m = 1;
                else
                    m = -1;
                
                result[(int)(result[0].value)].value = m*temp1;
            }
        }

    transSparse(result, result1);
    Multiply_Sparse(result1, 1/determinant(array), result2);
    printSparseMatrix(result2);  
}

int main(void) {
    matrix array1[LEN], array2[LEN], temp[LEN];
    int count;
    double scalar;
    
    while(1) {
        printf("Operations on Sparse Matrix:");
        printf("\n1.Input a Matrix");
        printf("\n2.Add two Matrices");
        printf("\n3.Multiply two Matrices");
        printf("\n4.Transpose a Matrix");
        printf("\n5.Multiply matrix with a Scalar");
        printf("\n6.Determinant of Matrix");
        printf("\n7.Invert a Matrix");
        printf("\n8.Quit ");
        printf("\nEnter choice: ");
        scanf("%d", &count);
        switch(count){
            case 1: 
                
                inputSparseMatrix(array1);
                break;
            
            case 2:
                inputSparseMatrix(array1);
                inputSparseMatrix(array2);
                
                addSparse(array1, array2, temp);
                break;
            case 3:
                inputSparseMatrix(array1);
                inputSparseMatrix(array2);

                Multiply(array1, array2, temp);
                break;
            case 4:
                inputSparseMatrix(array1);
                transSparse(array1, temp);
                break;
            case 5:
                inputSparseMatrix(array1);
                printf("\nScalar: ");
                scanf("%lf", &scalar);
                
                Multiply_Sparse(array1, scalar, temp);
                break;
            case 6:
                inputSparseMatrix(array1);
                if(array1[0].r != array1[0].c){
                    printf("Number of rows and column are not same\n");
                    break;      
                }
                printf("The determinant is: %lf\n", determinant(array1));
                break;
        case 7:
                inputSparseMatrix(array1);
                inverse(array1, array2);
                break;
        case 8:
                return 0;
        default:
                printf("Input is invalid\n");
                break;
        }
                
    }
    return 0;
}
