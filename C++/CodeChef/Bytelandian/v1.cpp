#include <iostream>
#include <map>

using namespace std;

typedef long long int Int;

map<Int,Int> arr;

void compute (Int n) {
	if(arr.count(n)==0) {
		if(arr.count(n/2)==0)
			compute(n/2);
		if(arr.count(n/3)==0)
			compute(n/3);
		if(arr.count(n/4)==0)
			compute(n/4);
		Int val = arr[n/2] + arr[n/3] + arr[n/4];
		if(val>n)
			arr[n] = val;
		else
			arr[n] = n;
	}
}

int main() {
	arr[0] = 0;
	arr[1] = 1;
	Int n;
	while(cin>>n) {
		compute(n);
		cout<<arr[n]<<endl;
	}
}
