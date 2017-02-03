#include <stdio.h>
#include <stdlib.h>
typedef struct{
    double value;
    unsigned int r, c;
}matrix;
void SortSparseMatrix(matrix *array){
    int count, j, cond;
    matrix t;
    for(count=2; count<array[0].value+1; ++count){
        j=count-1;
        t=array[count];
        cond = array[j].r>t.r || (array[j].r==t.r && array[j].c>t.c);
        while(cond && j>0){
            array[j+1]=array[j];
            --j;
            cond = array[j].r>t.r || (array[j].r==t.r && array[j].c>t.c);
        }
        array[j+1]=t;
    }
}
void printSparseMatrix(matrix *array){
    int count,i,j;
    printf("\n");
    if(array==NULL)
	return;
    double M[1000][1000]={0};
    for(count=1; count<=array[0].value; ++count)
        M[array[count].r][array[count].c]=array[count].value;
    for(i=1;i<=array[0].r;i++){
	for(j=1;j<=array[0].c;j++)
		printf("%.2lf ",M[i][j]);
     printf("\n");
}	
}

matrix *inputSparseMatrix(){
    int i,j;
    double input;
    matrix *array;
    array=malloc(sizeof(matrix));
    printf("\nENTER THE DIMENSIONS OF THE MATRIX: ");
    scanf("%d %d", &array[0].r, &array[0].c);
    array[0].value=0;
    printf("ENTER THE MATRIX : \n");
    for(i=1; i<=array[0].r; ++i)
        for(j=1;j<=array[0].c; ++j){
		scanf("%lf",&input);
		if(input){
 		array=realloc(array, ((int)(++array[0].value)+1)*sizeof(matrix));
		array[(int)array[0].value].r=i;
		array[(int)array[0].value].c=j;
		array[(int)array[0].value].value=input;
		}       
    }
    SortSparseMatrix(array);
    printSparseMatrix(array);
    return array;
}
matrix *addSparse(matrix *array1, matrix *array2){
    int count, j, f;
    matrix *array;
    if(array1[0].c!=array2[0].c || array1[0].r!=array2[0].r){
        printf("\nINVALID DIMENSIONS OF TWO MATRICES TO BE ADDED.");
        return NULL;
    }
    array=malloc(sizeof(matrix));
    array[0].c=array1[0].c;
    array[0].r=array1[0].r;
    array[0].value=0;
    for(count=1; count<=array1[0].value; ++count){
        array=realloc(array, (int)(++(array[0].value)+1)*sizeof(matrix));
        array[count].r=array1[count].r;
        array[count].c=array1[count].c;
        array[count].value=array1[count].value;
        for(j=1; j<=array2[0].value; ++j)
            if(array2[j].r==array1[count].r && array2[j].c==array1[count].c)
                array[count].value+=array2[j].value;
    }
    for(count=1; count<=array2[0].value; ++count){
        f=1;
        for(j=1; j<=array1[0].value; ++j)
            if(array2[count].r==array1[j].r && array2[count].c==array1[j].c){
                f=0;
                break;
            }
        if(f){
            array=realloc(array, (int)(++(array[0].value)+1)*sizeof(matrix));
            array[(int)array[0].value].r=array2[count].r;
            array[(int)array[0].value].c=array2[count].c;
            array[(int)array[0].value].value=array2[count].value;
        }
    }
    SortSparseMatrix(array);
    return array;
}

matrix *Multiply(matrix *array1, matrix *array2){
    int count, j, k, l, cond;
    double sum;
    matrix *array;
    if(array1[0].c!=array2[0].r){
        printf("\n THE MATRICES ARE NOT MULTIPLICABLE\n");
        return NULL;
    }
    array=malloc(sizeof(matrix));
    array[0].r=array1[0].r;
    array[0].c=array2[0].c;
    array[0].value=0;
    for(count=1; count<=array1[0].r; ++count)
        for(j=1; j<=array2[0].c; ++j){
            sum=0;
            for(k=1; k<=array1[0].value; ++k)
               for(l=1; l<=array2[0].value; ++l){
                   cond = array1[k].r==count && array2[l].c==j && array1[k].c==array2[l].r;
                   if(cond)
                       sum+=array1[k].value*array2[l].value;
               }
            if(sum){
                array=realloc(array, (int)(++(array[0].value)+1)*sizeof(matrix));
                array[(int)array[0].value].r=count;
                array[(int)array[0].value].c=j;
                array[(int)array[0].value].value=sum;
            }
        }   
    SortSparseMatrix(array);    
    return array;
}
matrix *Multiply_Sparse(matrix *array, double scalar){
    int count;
    matrix *array1;
    if(scalar==0){
    array1=malloc(sizeof(matrix));
    array1[0].c=array[0].c;
    array1[0].r=array[0].r;
    array1[0].value=0;
    return array1;
}
    for(count=1; count<=array[0].value; ++count)
        array[count].value*=scalar;
    return array;
}
matrix *transSparse(matrix *array){
    int count, t;
    for(count=0; count<array[0].value+1; ++count){
        t=array[count].r;
        array[count].r=array[count].c;
        array[count].c=t;
    }
    SortSparseMatrix(array);
    return array;
}
double determinant(matrix *array){
if(array[0].value==0)
return 0;
int j=array[1].r,i,m,c;
if(array[0].r==1 && (int)array[0].value==1)
return array[1].value;
else if(array[0].r==1 && (int)array[0].value==0)
return 0;
double det=0;
if(j>1)
return 0;
for(i=1;i<array[0].value;++i)
{
if(array[i].r>j)
break;
matrix *temp=malloc(sizeof(matrix));
temp[0].r=temp[0].c=array[0].r-1;
temp[0].value=0;
for(c=i+1;c<=array[0].value;++c)
if(array[c].r>array[i].r && array[c].c!=array[i].c)
{
temp=realloc(temp,(int)((++temp[0].value)+1)*sizeof(matrix));
temp[(int)(temp[0].value)].value=array[c].value;
temp[(int)(temp[0].value)].r=array[c].r-1;
if(array[i].c>array[c].c)
temp[(int)(temp[0].value)].c=array[c].c;
else
temp[(int)(temp[0].value)].c=array[c].c-1;
}
if(array[i].c%2==0)
m=-1;
else
m=1;
SortSparseMatrix(temp);
det=det+m*determinant(temp)*(array[i].value);
free(temp);
}
return det;
}

matrix *inverse(matrix *array){
int i,j,count;
double temp1,m;
if(array[0].r!=array[0].c){
printf("MATRIX IS NOT INVERTIBLE\n");
return NULL;
}

if(determinant(array)==0){
printf("MATRIX IS NOT INVERTIBLE\n");
return NULL;
}
matrix *result=malloc(sizeof(matrix));
result[0].r=array[0].r;
result[0].c=array[0].c;
result[0].value=0;
for(i=1;i<=array[0].r;i++)
	for(j=1;j<=array[0].c;j++){
matrix *temp=malloc(sizeof(matrix));
temp[0].r=array[0].r-1;
temp[0].c=array[0].c-1;
temp[0].value=0;
for(count=1;count<=array[0].value;count++)
if(array[count].r!=i && array[count].c!=j){
temp=realloc(temp,(int)((++temp[0].value)+1)*sizeof(matrix));
if(array[count].c<j)
temp[(int)(temp[0].value)].c=array[count].c;
else
temp[(int)(temp[0].value)].c=array[count].c-1;
if(array[count].r<i)
temp[(int)(temp[0].value)].r=array[count].r;
else
temp[(int)(temp[0].value)].r=array[count].r-1;
temp[(int)(temp[0].value)].value=array[count].value;
}
SortSparseMatrix(temp);
temp1=determinant(temp);
if(temp1){
result=realloc(result,(int)((++result[0].value)+1)*sizeof(matrix));
result[(int)(result[0].value)].r=i;
result[(int)(result[0].value)].c=j;
if((i+j)%2==0)
m=1;
else
m=-1;
result[(int)(result[0].value)].value=m*temp1;
}
free(temp);
}
matrix *result1=transSparse(result);
matrix *result2=Multiply_Sparse(result1,1/determinant(array));
return result2;
}

int main(void){
    matrix *array1, *array2, *temp;
    int count;
    double scalar;
    while(1) {
        printf("\nCHOOSE ON OF THE FOLLOWING \n:"); 
        printf("\n1.INPUT THE MATRIX");
        printf("\n2.ADD TO SPARSE MATRICES");
        printf("\n3.MULTIPLY TWO SPARSE MATRICES");
        printf("\n4.TRANSPOSE A SPARSE MATRIX");
        printf("\n5.MULTILY A SPARSE MATRIX WITH A SCALAR");
        printf("\n6.DETERMINANT A MATRIX");
	printf("\n7.INVERSE A MATRIX");
        printf("\n8.EXIT\n : ");
        scanf("%d", &count);
        switch(count){
            case 1:	
		array1=inputSparseMatrix();
		free(array1);
		break;
            case 2:
		array1=inputSparseMatrix();
		array2=inputSparseMatrix();
		if((temp=addSparse(array1, array2))!=NULL){
		printf("\nSUM OF THE MATRICES ARE : ");
		printSparseMatrix(temp);
		free(temp);}
		free(array1);
		free(array2);		
		break;
            case 3:
		array1=inputSparseMatrix();
		array2=inputSparseMatrix();
		if((temp=Multiply(array1, array2))!=NULL){
		printf("\nPRODUCT OF THE MATRICES ARE: ");
		printSparseMatrix(temp);
		free(temp);
		}
		free(array1);
		free(array2);		
		break;
            case 4:
		array1=inputSparseMatrix();
		printf("\nTRANSPOSE OF THE MATRICES ARE : ");
		temp=transSparse(array1);
		printSparseMatrix(temp);
		free(array1);		
		break;
            case 5:
		array1=inputSparseMatrix();
		printf("\nENTER A SCALAR : ");
		scanf("%lf", &scalar);
		printf("\nPRODUCT : ");
		temp=Multiply_Sparse(array1, scalar);
		printSparseMatrix(temp);
		free(array1);
		if(scalar==0)
		    free(temp);		
		break;
            case 6:
		array1=inputSparseMatrix();
		if(array1[0].r!=array1[0].c){
		printf("NUMBER OF ROWS AND COLUMN ARE NOT SAME\n");
			break;		
		}
		printf("THE DETERMINANT IS: %lf\n",determinant(array1));
		free(array1);
		break;
	    case 7:
		array1=inputSparseMatrix();
		printSparseMatrix(inverse(array1));  
		free(array1);
		break;
	    case 8:
            	return 0;
            default:
            	printf("INPUT IS INVALID\n");
            	break;
        }
                
    }
    return 0;
}
