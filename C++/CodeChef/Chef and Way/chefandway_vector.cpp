#include <iostream>
#include <vector>

using namespace std;

typedef long long int Int;

const Int Mod = (Int)1E9 + 7;

int main() {
	Int N,K;
	cin>>N>>K;
	vector<Int> V(N,Mod);
	for (Int i=0; i<N; ++i) {
		cin>>V[i];
	}
	cout<<endl<<endl<<N<<"\t"<<K<<endl;
	Int pos = 0, element_min = V[0], p_min = 1, answer=1;
	while (pos+K<N) {
		cout<<pos<<endl;
		element_min = V[pos];
		p_min = pos+1;
		for (Int i=1; i<=K; ++i) {
			if (V[pos+i]<=element_min) {
				element_min = V[pos+i];
				p_min = pos+i;
			}
		}
		pos = p_min;
		answer *= V[pos];
		answer %= Mod;
	}
	answer *= V[N-1];
	answer %= Mod;
	cout<<answer;
	return 0;
}