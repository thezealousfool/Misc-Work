#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

typedef long long int Int;

int main() {
	int T;
	cin>>T;
	while(T--) {
		Int N;
		cin>>N;
		vector<Int> inp(N);
		for(Int i=0; i<N; ++i)
			cin>>inp[i];
		sort(inp.begin(),inp.end());
		for(Int i=0; i<N; i+=2) {
			if(inp[i]!=inp[i+1]) {
				cout<<inp[i]<<endl;
				break;
			}
		}
	}
	return 0;
}