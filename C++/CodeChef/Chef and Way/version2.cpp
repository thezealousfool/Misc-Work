#include <iostream>
#include <vector>
#include <cmath>

using namespace std;
typedef long long int Int;
typedef long double Dob;

#define Mod 1000000007

void find_min (vector<Int>& inp, vector<double>& log_inp,vector<bool>& min_or_not, Int n, Int& K) {
	Int k = 1, min_k=1;
	double min;
	if (!min_or_not[n-k])
		find_min(inp,log_inp,min_or_not,n-k,K);
	min = log_inp[n-k] + log_inp[n];
	k = 2;
	while ((n-k>=0)&&(k<=K)) {
		double temp = log_inp[n-k] + log_inp[n];
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
	Int N, K;
	cin>>N>>K;
	vector<bool> min_or_not(N,false);
	vector<Int> inp(N);
	vector<double> log_inp(N);
	for (Int i = 0; i<N; ++i) {
		cin>>inp[i];
		log_inp[i] = log10(inp[i]);
	}
	inp[0] %= Mod;
	min_or_not[0] = true;
	find_min(inp,log_inp,min_or_not,N-1,K);
	cout<<inp[N-1];
	return 0;
}