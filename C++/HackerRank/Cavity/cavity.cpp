#include<iostream>
#include<stdio.h>
using namespace std;

int main() {
	int n;
	cin>>n;
	int a[100][100];
	int b[100][100];
	getchar();
	for (int i = 0; i < n; ++i)
	{
		for (int j = 0; j < n; ++j)
		{
			char ch = getchar();
			a[i][j] = int(ch)-int('0');
			b[i][j] = a[i][j];
		}
		getchar();
	}
	for (int i = 1; i < n-1; ++i)
	{
		for (int j = 1; j < n-1; ++j)
		{
			if ( a[i-1][j] < a[i][j] && a[i+1][j] < a[i][j] && a[i][j-1] < a[i][j] && a[i][j+1] < a[i][j] )
			{
				b[i][j] = -1;
			}
		}
	}
	for (int i = 0; i < n; ++i)
	{
		for (int j = 0; j < n; ++j)
		{
			if (b[i][j]==-1)
				cout<<"X";
			else
				cout<<b[i][j];
		}
		cout<<endl;
	}
}