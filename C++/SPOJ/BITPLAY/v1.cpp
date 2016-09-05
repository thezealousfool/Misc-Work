#include <iostream>
#include <vector>
#include <deque>
#include <cmath>

using namespace std;

typedef long long int Int;

deque<int> binary;

void populate_queue(Int& n) {
	while(!binary.empty()) binary.pop_back();
	while(n>0) {
		binary.push_back((int)(log2(n)));
		n -= (Int)(pow(2,binary.back()));
	}
}

void compute() {
	Int N; int K;
	cin>>N>>K;
	if(K<=0) {
		cout<<-1<<endl;
		return;
	}
	Int n = N;
	populate_queue(n);
	if(binary.size() < K) {
		n = N-1;
		populate_queue(n);
	}
	while(binary.size() >= K)
		binary.pop_back();
	n=0;
	while(!binary.empty()) {
		n += (Int)(pow(2,binary.front()));
		binary.pop_front();
	}
	if(n%2==0)
		++n;
	cout<<n<<endl;
}

int main() {
	binary.resize(30);
	int T;
	cin>>T;
	while(T--) {
		compute();
	}
	return 0;
}