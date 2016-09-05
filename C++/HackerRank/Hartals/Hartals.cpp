/*
 * Hartals.cpp
 *
 *  Created on: 03-Oct-2015
 *      Author: vivu
 */

#include <iostream>

using namespace std;

int days[3650],parties[100],x=0,z=0,output[100];

void initArray(int *a, int y)
{
	for (int i=0; i<y; i++)
	{
		a[i]=0;
	}
}

void input()
{
	cin>>x;
	days[x];
	initArray(days,x);
	cin>>z;
	parties[z];
	initArray(parties,z);
	for (int i=0; i<z; i++)
	{
		cin>>parties[i];
	}
}

int compute()
{
	int y=0,w=0,count=0;
	for(int i=0; i<z; i++)
	{
		y=parties[i];
		w=x/y;
		for (int j=1; j<=w; j++)
		{
			if(days[j*y]!=1 && (j*y)%7!=0 && (j*y)%7!=6)
			{
				days[j*y]=1;
				count++;
			}
		}
	}
	return count;
}

void display(int *inp, int k)
{
	for (int i=0; i<k; i++)
	{
		cout<<inp[i]<<endl;
	}
}

int main()
{
	int numb=0;
	cin>>numb;
	for(int i=0 ;i<numb;i++)
	{
		input();
		output[i] = compute();
	}
	display(output,numb);
	return 0;
}
