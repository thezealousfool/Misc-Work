#include <iostream>
#include <stdlib.h>
#include <time.h>

using namespace std;

int main() {
	long long int n,mod,i;
	cout<<"N: ";
	cin>>n;
	cout<<"Mod: ";
	cin>>mod;
	srand(time(NULL));
	for(i=0; i<n; ++i) {
		cout<<rand()%mod<<" ";
	}
	return 0;
}