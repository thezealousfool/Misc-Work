#include <iostream>
#include <array>
#include <cmath>

using namespace std;
typedef long long int Int;
typedef long double Dob;

#define Mod 1000000007
#define Max 100001

array<Int,Max> inp;
array<bool,Max> min_or_not = {};
array<double,Max> log_inp;
Int N, K;

void find_min (Int n) {
	Int k = 1, min_k=1;
	double min;
	if (!min_or_not[n-k])
		find_min(n-k);
	min = log_inp[n-k];
	k = 2;
	while ((n-k>=0)&&(k<=K)) {
		double temp = log_inp[n-k];
		if (temp < min) {
			min_k = k;
			min = temp;
		}
		++k;
	}
	inp[n] *= inp[n-min_k];
	inp[n] %= Mod;
	log_inp[n] += log_inp[n-min_k];
	min_or_not[n] = true;
}

int main() {
	cin>>N>>K;
	for (Int i = 0; i<N; ++i) {
		cin>>inp[i];
		log_inp[i] = log10(inp[i]);
	}
	inp[0] %= Mod;
	min_or_not[0] = true;
	find_min(N-1);
	cout<<inp[N-1];
	return 0;
}