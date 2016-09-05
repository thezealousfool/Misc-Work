#include <iostream>
#include <vector>

using namespace std;

void rev(int &a) {
	int sum = 0;
	while(a>0) {
		sum = (sum*10) + (a%10);
		a /= 10;
	}
	a = sum;
}

int main() {
	int T;
	cin>>T;
	vector<int> res(T);
	for(int t=0; t<T; ++t) {
		int n1,n2,sum;
		cin>>n1>>n2;
		rev(n1); rev(n2);
		sum = n1+n2;
		rev(sum);
		res[t] = sum;
	}
	for(int t=0; t<T; ++t)
		cout<<res[t]<<endl;
}