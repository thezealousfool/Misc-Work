#include <stdio.h>
#include <stdlib.h>
#define MAX_ELEMS(m,n) ((m)*(n)/2)

typedef struct { int row, col, val; } triplet;
typedef struct { triplet* data; } matrix;

void deallocateMatrix(matrix* m)
{
    if(m == NULL)
        return;
    if((m->data) != NULL)
        free(m->data);
    free(m);
}

matrix* allocateMatrix(int rows, int cols)
{
    matrix* m = (matrix*)malloc(sizeof(matrix));
    if(m == NULL) {
        printf("Allocation Error!\nCould not allocate sufficient memory\nAborting\n");
        return NULL;
    }

    m->data = (triplet*)malloc((MAX_ELEMS(rows, cols) + 1)*sizeof(triplet));
    if((m->data) == NULL) {
        printf("Allocation Error!\nCould not allocate sufficient memory\nAborting\n");
        free(m);
        return NULL;
    }

    return m;
}

matrix* inputMatrix()
{
    int rows, cols, count = 0;
    int i, j, temp;
    triplet tripTemp;
    matrix* m;

    printf("No of Rows: ");
    scanf("%d", &rows);
    printf("No of Columns: ");
    scanf("%d", &cols);
    
    m = allocateMatrix(rows, cols);
    
    printf("Enter elements of Matrix:\n");
    for(i = 0; i < rows; ++i) {
        for(j = 0; j < cols; ++j) {
            
            scanf("%d", &temp);
            
            if(temp != 0)
                ++count;
            else
                continue;
            
            if(count > MAX_ELEMS(rows, cols)) {
                printf("Allocation Error!\nMatrix too dense.\nAborting!\n");
                deallocateMatrix(m);
                return NULL;
            }

            tripTemp.row = i;
            tripTemp.col = j;
            tripTemp.val = temp;
            (m->data)[count] = tripTemp;
        }
    }

    tripTemp.row = rows;
    tripTemp.col = cols;
    tripTemp.val = count;
    (m->data)[0] = tripTemp;

    return m;
}

triplet* findTrip(matrix* m, triplet t)
{
    int rows, cols, count;
    int i;
    
    if(m == NULL || (m->data) == NULL)
        return NULL;

    rows = (m->data)[0].row;
    cols = (m->data)[0].col;
    count = (m->data)[0].val;

    if(t.row > rows || t.col > cols)
        return NULL;

    for(i = 1; i <= count; ++i) {
        if((m->data)[i].row == t.row && (m->data)[i].col == t.col)
            return &((m->data)[i]);
    }
    return NULL;
}

void printMatrix(matrix* m)
{
    int rows, cols, count;
    int i, j, temp = 1;
    triplet tripTemp;
    triplet* pTriplet;

    if (m == NULL || (m->data) == NULL) {
        return;
    }

    rows = (m->data)[0].row;
    cols = (m->data)[0].col;
    count = (m->data)[0].val;

    for(i = 0; i < rows; ++i) {
        for(j = 0; j < cols; ++j) {
            tripTemp.row = i;
            tripTemp.col = j;
            tripTemp.val = 0;

            pTriplet = findTrip(m, tripTemp);
       
            if(pTriplet == NULL)
                printf("%3d ", 0);
            else
                printf("%3d ", pTriplet->val);
        }
        printf("\n");
    }
}

matrix* addMatrices(matrix* m1, matrix* m2)
{
    int rows, cols, count = 0;
    int i, j, temp;
    triplet tripTemp;
    triplet* pTriplet;
    matrix* m;

    if(m1 == NULL || m2 == NULL || (m1->data) == NULL || (m2->data) == NULL)
        return NULL;

    rows = (m1->data)[0].row;
    cols = (m1->data)[0].col;

    if((rows != (m2->data)[0].row) || (cols != (m2->data)[0].col)) {
        printf("Assertion Error!\nMatrices sizes should match\n");
        return NULL;
    }

    m = allocateMatrix(rows, cols);

    for(i = 0; i < rows; ++i) {
        for(j = 0; j < cols; ++j) {
            tripTemp.row = i;
            tripTemp.col = j;
            tripTemp.val = 0;
            
            pTriplet = findTrip(m1, tripTemp);
       
            if(pTriplet == NULL) {
                pTriplet = findTrip(m2, tripTemp);

                if(pTriplet != NULL) {
                    ++count;
                    if(count > MAX_ELEMS(rows, cols)) {
                        printf("Allocation Error!\nMatrix too dense.\nAborting!\n");
                        deallocateMatrix(m);
                        return NULL;
                    }
                    tripTemp.val = pTriplet->val;
                    (m->data)[count] = tripTemp;
                }
            }
            else {
                temp = pTriplet->val;
                pTriplet = findTrip(m2, tripTemp);

                if(pTriplet == NULL) {
                    ++count;
                    if(count > MAX_ELEMS(rows, cols)) {
                        printf("Allocation Error!\nMatrix too dense.\nAborting!\n");
                        deallocateMatrix(m);
                        return NULL;
                    }
                    tripTemp.val = temp;
                    (m->data)[count] = tripTemp;
                }
                else {
                    ++count;
                    if(count > MAX_ELEMS(rows, cols)) {
                        printf("Allocation Error!\nMatrix too dense.\nAborting!\n");
                        deallocateMatrix(m);
                        return NULL;
                    }
                    tripTemp.val = temp + pTriplet->val;
                    (m->data)[count] = tripTemp;
                }
            }
        }
    }

    tripTemp.row = rows;
    tripTemp.col = cols;
    tripTemp.val = count;
    (m->data)[0] = tripTemp;

    return m;
}

matrix* sMultMatrix(matrix* m1, int val)
{
    int count = 0;
    int i;
    matrix* m;

    if(m1 == NULL || (m1->data) == NULL)
        return NULL;

    count = (m1->data)[0].val;

    m = allocateMatrix((m1->data)[0].row, (m1->data)[0].col);

    for(i = 1; i <= count; ++i) {
        (m->data)[i].row = (m1->data)[i].row;
        (m->data)[i].col = (m1->data)[i].col;
        (m->data)[i].val = val * (m1->data)[i].val;
    }

    (m->data)[0] = (m1->data)[0];

    return m;
}

matrix* transMatrix(matrix* m1)
{
    int count = 0;
    int i;
    matrix* m;

    if(m1 == NULL || (m1->data) == NULL)
        return NULL;

    count = (m1->data)[0].val;

    m = allocateMatrix((m1->data)[0].row, (m1->data)[0].col);

    for(i = 0; i <= count; ++i) {
        (m->data)[i].row = (m1->data)[i].col;
        (m->data)[i].col = (m1->data)[i].row;
        (m->data)[i].val = (m1->data)[i].val;
    }

    return m;
}

matrix* mMultMatrix(matrix* m1, matrix* m2)
{
    int rows, cols, iter, count = 0;
    int i, j, k, temp;
    triplet tripTemp;
    triplet* pTriplet;
    matrix* m;

    if(m1 == NULL || m2 == NULL || (m1->data) == NULL || (m2->data) == NULL)
        return NULL;

    rows = (m2->data)[0].row;
    cols = (m1->data)[0].col;

    if(cols != rows) {
        printf("Assertion Error!\nMatrices sizes should match\n");
        return NULL;
    }

    iter = rows;
    rows = (m1->data)[0].row;
    cols = (m2->data)[0].col;

    m = allocateMatrix(rows, cols);

    for(i = 0; i < rows; ++i) {
        for(j = 0; j < cols; ++j) {
            for(k = 0; k < iter; ++k) {
                tripTemp.row = i;
                tripTemp.col = k;
                tripTemp.val = 0;
                
                pTriplet = findTrip(m1, tripTemp);
           
                if(pTriplet != NULL) {
                    temp = pTriplet->val;

                    tripTemp.row = k;
                    tripTemp.col = j;

                    pTriplet = findTrip(m2, tripTemp);

                    if(pTriplet != NULL) {
                        temp = (pTriplet->val) * temp;

                        tripTemp.row = i;
                        tripTemp.col = j;

                        pTriplet = findTrip(m, tripTemp);

                        if(pTriplet == NULL) {
                            ++count;
                            if(count > MAX_ELEMS(rows, cols)) {
                                printf("Allocation Error!\nMatrix too dense.\nAborting!\n");
                                deallocateMatrix(m);
                                return NULL;
                            }
                            tripTemp.val = temp;
                            (m->data)[count] = tripTemp;
                        }
                        else {
                            (pTriplet->val) += temp;
                        }

                        tripTemp.row = rows;
                        tripTemp.col = cols;
                        tripTemp.val = count;
                        (m->data)[0] = tripTemp;
                    }
                }
            }
        }
    }

    return m;
}

int main(void)
{
    int choice, scalar;
    matrix *array1, *array2, *temp;

    while(1) {
        printf("Operations on Sparse Matrix:");
        printf("\n1.Input a Matrix");
        printf("\n2.Add two Matrices");
        printf("\n3.Multiply two Matrices");
        printf("\n4.Transpose a Matrix");
        printf("\n5.Multiply matrix with a Scalar");
        printf("\n6.Invert a Matrix");
        printf("\n7.Quit ");
        printf("\nEnter choice: ");
        scanf("%d", &choice);
        switch(choice){
            case 1: 
                    array1 = inputMatrix();
                    printMatrix(array1);
                    deallocateMatrix(array1);
                    break;
            case 2:
                    printf("\nFirst Matrix:\n");
                    array1 = inputMatrix();

                    printf("\nSecond Matrix:\n");
                    array2 = inputMatrix();
                    
                    printf("\nSum:\n");
                    temp = addMatrices(array1, array2);
                    printMatrix(temp);
                    
                    deallocateMatrix(array1);
                    deallocateMatrix(array2);
                    deallocateMatrix(temp);
                    break;
            case 3:
                    printf("\nFirst Matrix:\n");
                    array1 = inputMatrix();

                    printf("\nSecond Matrix:\n");
                    array2 = inputMatrix();
                    
                    printf("\nProduct:\n");
                    temp = mMultMatrix(array1, array2);
                    printMatrix(temp);

                    deallocateMatrix(array1);
                    deallocateMatrix(array2);
                    deallocateMatrix(temp);
                    break;
            case 4:
                    printf("\nMatrix: \n");
                    array1 = inputMatrix();

                    printf("\nTranspose:\n");
                    temp = transMatrix(array1);
                    printMatrix(temp);

                    deallocateMatrix(array1);
                    deallocateMatrix(temp);
                    break;
            case 5:
                    printf("\nMatrix: \n");
                    array1 = inputMatrix();
                    
                    printf("\nScalar: ");
                    scanf("%d", &scalar);
                    
                    printf("\n\nProduct:\n");
                    temp = sMultMatrix(array1, scalar);
                    printMatrix(temp);
                    
                    deallocateMatrix(array1);
                    deallocateMatrix(temp);
                    break;
            // case 6:
            //         printf("\nMatrix: \n");
            //         array1 = inputMatrix();
                    
            //         printf("\n\nInverse:\n");
            //         temp = InvMatrix(array1, scalar);
            //         printMatrix(temp);
                    
            //         deallocateMatrix(array1);
            //         deallocateMatrix(temp);
            //         break;
            case 7:
                    return 0;
            default:
                    printf("Invalid Input\n");
                    break;
        }
    }
    return 0;
}
