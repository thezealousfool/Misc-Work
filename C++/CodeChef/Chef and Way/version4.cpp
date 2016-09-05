#include <iostream>
#include <array>
#include <cmath>

using namespace std;
typedef long long int Int;

#define Mod 1000000007
#define Max 100001

array<Int,Max> inp;
array<double,Max> log_inp;
Int N, K;

void find_min (Int n) {
	Int k = 2, min_k=1;
	double min = log_inp[n-1];
	while ((n-k>=0)&&(k<=K)) {
		if (log_inp[n-k] < min) {
			min_k = k;
			min = log_inp[n-k];
		}
		++k;
	}
	inp[n] = (inp[n]*inp[n-min_k])%Mod;
	log_inp[n] += log_inp[n-min_k];
}


int main() {
	cin>>N>>K;
	for (Int i = 0; i<N; ++i) {
		cin>>inp[i];
		log_inp[i] = log10(inp[i]);
	}
	inp[0] %= Mod;
	for (Int i = 1; i<N; ++i) {
		find_min(i);
	}
	cout<<inp[N-1];
	return 0;
}