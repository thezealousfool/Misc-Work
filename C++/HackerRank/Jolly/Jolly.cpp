

#include <iostream>

using namespace std;

int n, inp[3000];

void input()
{
	cin>>n;
	for (int i=0; i<n; i++)
		cin>>inp[i];
}

void computeArray()
{
	for(int i=0; i<n-1; i++)
	{
		inp[i]=inp[i]>inp[i+1]?inp[i]-inp[i+1]:inp[i+1]-inp[i];
	}
}

void sort()
{
	int temp;
	for (int i=0; i<n-1; i++)
	{
		for (int j=0; j<n-2; j++)
		{
			if(inp[j]>inp[j+1])
			{
				temp=inp[j];
				inp[j]=inp[j+1];
				inp[j+1]=temp;
			}
		}
	}
}

int check()
{
	for (int i=0; i<n-1; i++)
	{
		if(inp[i]!=i+1)
			return 1;
	}
	return 0;
}

void display(int k)
{
	for (int i=0; i<k; i++)
	{
		cout<<inp[i]<<endl;
	}
}

int main()
{
	input();
	computeArray();
	sort();
	if(check())
		cout<<"Not jolly";
	else
		cout<<"Jolly";
	return 0;
}
