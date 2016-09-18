#include <iostream>

using namespace std;

typedef long long int Int;

void compute() {
	Int N,K,count;
	cin>>N>>K;
	count = 0;
	for(Int i=0; i<N; ++i) {
		Int temp;
		cin>>temp;
		Int nearest = (Int)(temp/K);
		Int left = temp - nearest*K;
		Int right = (nearest+1)*K - temp;
		if(left==temp) {
			count += K-left;
			continue;
		}
		if(left<right)
			count += left;
		else
			count += right;
	}
	cout<<count<<endl;
}

int main() {
	int T;
	cin>>T;
	for (int i=0; i<T; ++i)
		compute();
	return 0;
}