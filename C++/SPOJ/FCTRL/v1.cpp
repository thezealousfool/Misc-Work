/*input
3
5
15
25
*/#include <iostream>
#include <vector>

using namespace std;

int main() {
	int T;
	cin>>T;
	vector<int> res(T);
	for(int t=0; t<T; ++t) {
		int n;
		cin>>n;
		int ans = 0;
		while(n>0) {
			ans += n/5;
			n /= 5;
		}
		res[t] = ans;
	}
	for(int t=0; t<T; ++t)
		cout<<res[t]<<endl;
}