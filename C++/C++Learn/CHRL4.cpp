#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>
#include <cmath>
#include <cfloat>

using namespace std;

typedef long long int Int;
typedef long double Dob;

#define Mod 1000000007
#define Max 100010

vector<Int> weights;
vector<Dob> log_weights;
vector<Int> pqueue;
vector<Int> dist;
vector<Dob> pseudo_dist;

Int N,K;


int main() {

	// weights.reserve(Max);
	// log_weights.reserve(Max);
	// pqueue.reserve(Max);
	// dist.reserve(Max);
	// pseudo_dist.reserve(Max);

	cin>>N>>K;
	
	weights.resize(N);
	log_weights.resize(N);
	pqueue.resize(N);
	dist.resize(N);
	pseudo_dist.resize(N);


	for(Int i=0; i<N; ++i) {

		Int temp;
		cin>>temp;

		weights[i] = (temp);
		log_weights[i] = (log10(temp));

		pqueue[i] = (i);
		dist[i] = (LLONG_MAX);
		pseudo_dist[i] = (log10(LLONG_MAX)*10);
	}

	dist[0] = weights[0]%Mod;
	pseudo_dist[0] = log_weights[0];


	auto min = [](const Int& n1,const Int& n2){return pseudo_dist[n2]<pseudo_dist[n1];};


	while(pqueue.size()!=0) {

		Int min_element = pqueue.front();
		pop_heap(pqueue.begin(), pqueue.end(), min);
		pqueue.pop_back();

		for(Int i=1; i<=K; ++i) {
			Int tmp_index = min_element + i;
			if(tmp_index<weights.size()) {
				Dob old_dist = pseudo_dist[tmp_index];
				Dob new_dist = pseudo_dist[min_element] + log_weights[tmp_index];
				
				if(new_dist < old_dist) {
					pseudo_dist[tmp_index] = new_dist;
					dist[tmp_index] = (dist[min_element] * weights[tmp_index]) % Mod;
					push_heap(pqueue.begin(),pqueue.begin()+i,min); 
				}
			}
		}

	}

	cout<<dist[N-1];
	return 0;
}