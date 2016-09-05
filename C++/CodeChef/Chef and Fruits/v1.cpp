#include <iostream>

using namespace std;

int ans[101];

int main() {
	int T,N,M,K,req;
	cin>>T;
	for (int i=0; i<T; ++i) {
		cin>>N>>M>>K;
		req=abs(N-M);
		if (K>=req)
			ans[i] = 0;
		else
			ans[i] = req-K;
	}
	for (int i = 0; i<T; ++i)
		cout<<ans[i]<<endl;
	return 0;
}