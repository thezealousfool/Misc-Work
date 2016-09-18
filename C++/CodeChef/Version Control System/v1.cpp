#include <iostream>
#include <vector>

using namespace std;

void compute() {
	int N,M,K;
	cin>>N>>M>>K;
	vector<int> files(N+1);
	int sum1 = 0, sum2 = 0;
	for(int i=0; i<M; ++i){
		int temp;
		cin>>temp;
		++files[temp];
	}
	for(int i=0; i<K; ++i){
		int temp;
		cin>>temp;
		++files[temp];
	}
	for(int i=1; i<=N; ++i){
		if(files[i]==2)
			++sum1;
		else if(files[i]==0)
			++sum2;
	}
	cout<<sum1<<" "<<sum2<<endl;
}

int main() {
	int T;
	cin>>T;
	while(T--)
		compute();
	return 0;
}