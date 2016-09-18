#include <stdio.h>
#include <math.h>

int main()
{
    int i,j,k,n,iter;
    float x[10],y[10],z[10],a[10][10],l,d,f,e,Z;
    printf("\nEnter the order of the matrix : \n");
    scanf("%d",&n);
    printf("\nEnter the number of Iterations : \n");
    scanf("%d",&iter);
    printf("\nEnter the coefficients of the matrix row wise :\n");
    for(i=0;i<n;i++)
    {
        for(j=0;j<n;j++)
        {
            scanf("%f",&a[i][j]);
        }
        x[i]=1;
    }
    k=0;
    line:
    for(i=0;i<n;i++)
    {
        y[i]=0;
        for(j=0;j<n;j++)
        {
            y[i]=y[i]+a[i][j]*x[j];
        }
        z[i]=fabs(y[i]);
    }
    Z=z[0];
    j=0;
    for(i=1;i<n;i++)
    {
        if(z[i]>=Z)
        {
            Z=z[i];
            j=i;
        }
    }
    if(Z==y[j])
    {
        d=Z;
    }
    else
    {
        d=-Z;
    }
    for(i=0;i<n;i++)
    {
        x[i]=y[i]/d;
    }
    k++;
    if(k>=iter)
    {
        printf("\nThe numerically largest Eigen value is %f \n",d);
    }
    else
    {
        goto line;
    }
    return 0;
}
