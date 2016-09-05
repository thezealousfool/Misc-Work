#include <iostream>
#include <vector>
using namespace std;

typedef long long int Int;

int main() {
	int T;
	cin>>T;
	vector<Int> v(T);
	for(int t=0; t<T; ++t) {
		Int E,N;
		cin>>E>>N;
		Int count = 0;
		while(E>0 && N>0) {
			if(E<2 && N<2) {
				break;
			}
			if(E>N) {
				E -= 2;
				--N;
			}
			else {
				N -= 2;
				--E;
			}
			++count;
		}
		v[t] = count;
	}
	for(int t=0; t<T; ++t) {
		cout<<v[t]<<endl;
	}
}