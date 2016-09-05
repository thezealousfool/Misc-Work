#include <iostream>
#include <vector>

using namespace std;
typedef long long int Int;

Int sum (Int& k) {
	return (Int)((k*(k+1))/2);
}

Int compute() {
	Int N;
	cin>>N;
	vector<Int> inp(N);
	for (Int i = 0; i<N; ++i)
		cin>>inp[i];
	Int k = 1;
	Int value = 0;
	for (Int i = 0; i<N-1; ++i) {
		if (inp[i]<=inp[i+1]) {
			++k;
		}
		else {
			value += sum(k);
			k=1;
		}
	}
	value += sum(k);
	return value;
}


int main() {
	int N;
	cin>>N;
	vector<Int> out(N);
	for (int i = 0; i<N; ++i) {
		out[i] = compute();
	}
	for (int i = 0; i<N; ++i) {
		cout<<out[i]<<endl;
	}
}