#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;


typedef long long int Int;
int main() {
	int T;
	cin>>T;
	while(T--) {
		Int N; Int K;
		cin>>N>>K;
		vector<Int> first(N);
		vector<Int> second(N);
		int max = 0, min = 0;
		for(int i=0; i<N; ++i) {
			cin>>first[i];
		}
		for(int i=0; i<N; ++i) {
			cin>>second[i];
			max = second[i]>second[max]?i:max;
			min = second[i]<second[min]?i:min;
		}
		//Int val1 = first[max] + K;
		//Int val2 = first[min] - K;
		if((second[max])>(-1*second[min]))
			first[max] += K;
		else
			first[min] -= K;
		Int product = 0;
		for(int i=0; i<N; ++i) {
			product += first[i] * second[i];
		}
		cout<<product<<endl;
	}
	return 0;
}