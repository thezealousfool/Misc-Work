#include<stdio.h>
typedef struct{
unsigned int exponent;
double coeff;
}poly;
int search(poly p[100],int l,int h,int k)
	{
		int i;
		for(i=l;i<=h;i++)
			if(p[i].exponent==k)
				return i;
		return -1;
	}
void PrintPolynomial(poly p[100],int n)
    {
	int i;
	printf("%.2lfx^%u",p[0].coeff,p[0].exponent);
        for(i=1;i<n;i++){

          if(p[i].coeff>=0)
              printf("+%.2lfx^%u",p[i].coeff,p[i].exponent);
          else
              printf("-%.2lfx^%u",(-1)*p[i].coeff,p[i].exponent);
           }
        printf("\n");
    }
void inputPolynomial(poly p[100],int n)
	{
		int i,j;
		printf("ENTER THE COEFFICIENTS OF THE POLYNOMIAL IN ORDER\n");
		for(i=0;i<n;i++)
			scanf("%lf",&p[i].coeff);
		printf("ENTER THE DEGREE OF THE SAME POLYNOMIAL IN THE SAME ORDER\n");
		for(i=0;i<n;i++)
			scanf("%u",&p[i].exponent);
	        printf("THE POLYNOMIAL IS: ");
		PrintPolynomial(p,n);	
	}
void addPolynomial(poly p[100],poly q[100],poly result[100],int n1,int n2)
	{
		int i,j,k=0;
                int found[100]={0};
		for(i=0;i<n1;i++){
			int a;
			a=search(q,0,n2-1,p[i].exponent);                         
			if(a==-1){
				result[k].coeff=p[i].coeff;
				result[k].exponent=p[i].exponent;				
				k++;
			}
			else{
				result[k].coeff=p[i].coeff+q[a].coeff;
				result[k].exponent=p[i].exponent;
                                found[a]=1;
				k++;
			}
		}
		for(j=0;j<n2;j++){
			if(found[j]==0){
				result[k].exponent=q[j].exponent;
				result[k].coeff=q[j].coeff;
				k++;
			}
		}
		printf("THE RESULTANT POLYNOMIAL IS: ");
		PrintPolynomial(result,k);
	}
int checkZero(poly p[100],int n1){
		int i;
		for(i=0;i<n1;i++)
		    if(p[i].coeff!=0)
			return 0;
		return 1;

}
void multiplyPolynomial(poly p[100],poly q[100],poly result[100],int n1,int n2)
	{
		int i,j,k,m=0,a;
		for(i=0;i<n1;i++){
			for(j=0;j<n2;j++){
				a=search(result,0,m-1,p[i].exponent+q[j].exponent);
				if(a!=-1)
				    result[a].coeff+=p[i].coeff*q[j].coeff;
				else{
		        	    result[m].coeff=p[i].coeff*q[j].coeff;
		        	    result[m].exponent=p[i].exponent+q[j].exponent;
				    m++;
				}
			}
		}
		printf("THE RESULTANT POLYNOMIAL IS: ");
		PrintPolynomial(result,m);	
	}
int degreeOfPolynomial(poly p[100],int n)
	{
		int maximum_degree,i;
		maximum_degree=-1;
		for(i=0;i<n;i++){
			if(p[i].exponent>maximum_degree)
			maximum_degree=p[i].exponent;
		}
	 return maximum_degree;
	}
void subtractPolynomial(poly p[100],poly q[100],poly result[100],int n1,int n2)
	{
		int i,j,k=0;
                int found[100]={0};
		for(i=0;i<n1;i++){
			int a;
			a=search(q,0,n2-1,p[i].exponent);                         
			if(a==-1){
				result[k].coeff=p[i].coeff;
				result[k].exponent=p[i].exponent;				
				k++;
			}
			else{
				result[k].coeff=p[i].coeff-q[a].coeff;
				result[k].exponent=p[i].exponent;
                                found[a]=1;
				k++;
			}
		}
		for(j=0;j<n2;j++){
			if(found[j]==0){
				result[k].exponent=q[j].exponent;
				result[k].coeff=q[j].coeff*(-1);
				k++;
			}
		}
	PrintPolynomial(result,k);
	}
int main(void)
	{
		int choice,n1,n2,i;
                poly p[100],q[100],result[100];
		printf("PLEASE ENTER \n1 ADD TWO POLYNOMIALS\n2 TO SUBTRACT TWO POLYNOMIALS\n3 TO MULTIPLY TWO POLYNOMIALS\n4 TO FIND THE DEGREE OF THE ENTERED POLYNOMIAL\n5 TO CHECK IF THE POLYNOMIAL IS A ZERO POLYNOMIAL OR NOT\n");
		printf("ENTER THE CHOICE: ");
		scanf("%d",&choice);
		switch(choice)
			{
				case 1 :
					printf("ENTER THE NUMBER OF TERMS THE FIRST POLYNOMIAL AND THE SECOND POLYNOMAIL CONTAINS RESPECTIVELY\n");
					scanf("%d %d",&n1,&n2);
					printf("::FIRST::\n\n");inputPolynomial(p,n1);
					printf("::SECOND::\n\n");inputPolynomial(q,n2);
					addPolynomial(p,q,result,n1,n2);
					break;
		
				case 2 :	
					printf("ENTER THE NUMBER OF TERMS THE FIRST AND THE SECOND POLYNOMIAL HAVE RESPECTIVELY :\n");
					scanf("%d %d",&n1,&n2);
					printf("::FIRST::\n\n");inputPolynomial(p,n1);
					printf("::SECOND::\n\n");inputPolynomial(q,n2);
					subtractPolynomial(p,q,result,n1,n2);
					break;
		
		    	        case 3 :
					printf("ENTER THE NUMBER OF TERMS THE FIRST AND THE SECOND POLYNOMIAL HAVE RESPECTIVELY :\n");
					scanf("%d %d",&n1,&n2);
					printf("::FIRST::\n\n");inputPolynomial(p,n1);
					printf("::SECOND::\n\n");inputPolynomial(q,n2);
					multiplyPolynomial(p,q,result,n1,n2);
					break;
				
				case 4 :
				        printf("ENTER THE NUMBER OF TERMS THE POLYNOMIAL HAS :\n");
					scanf("%d",&n1);
					inputPolynomial(p,n1);
					printf("The degree of polynomial is: ");
				   	printf("%d\n",degreeOfPolynomial(p,n1));
					break;
				
				case  5 :
					printf("ENTER THE NUMBER OF TERMS THE POLYNOMIAL HAS :\n");
					scanf("%d",&n1);
					inputPolynomial(p,n1);
					if(checkZero(p,n1)==0)
						printf("IT IS NOT A ZERO POLYNOMIAL\n");
					else
						printf("IT IS A ZERO POLYNOMIAL\n");					
					break;		
				default:
					printf("INVALID INPUT\n\n");
   }	
		return 0;
	}
