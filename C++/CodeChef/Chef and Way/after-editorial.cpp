#include <iostream>
#include <vector>
#include <deque>
#include <cmath>

using namespace std;

typedef long long int Int;

#define Mod 1000000007
//#define Max 100005

int main() {

	int N,K;

	cin>>N>>K;

	vector<Int> weights(N);
	vector<double> log_weights(N);
	vector<Int> dist(N);
	vector<double> pseudo_dist(N);
	deque<Int> pq;


	for(Int i=0; i<N; ++i) {
		cin>>weights[i];
		log_weights[i] = log10(weights[i]) * 100;
	}
	dist[0] = weights[0]%Mod;
	pseudo_dist[0] = log_weights[0];
	pq.push_back(0);
	for(Int i=1; i<N; ++i) {
		while(pq.front()<(i-K))
			pq.pop_front();
		log_weights[i] = log_weights[pq.front()] + log_weights[i];
		weights[i] = (weights[pq.front()] * weights[i]) % Mod;
		while(log_weights[pq.back()]>log_weights[i] && !pq.empty())
			pq.pop_back();
		pq.push_back(i);
	}

	cout<<weights[N-1]<<endl;
}
