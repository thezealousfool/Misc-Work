#include <iostream>
#include <vector>

using namespace std;

const long long int Max = (long long int)1E9 + 7;

long long int find_min (long long int n,long long int& k, vector<long long int>& streets, vector<long long int>& minimum, vector<long double>& logmini) {
	 if(minimum[n]!=Max)
	 	return minimum[n];
	 else {
	 	long long int mini = find_min(n-1,k,streets,minimum,logmini)*(streets[n]);
	 	long long int i = 2;
	 	while (i<=k && n-i>=0) {
	 		long long int temp = find_min(n-i,k,streets,minimum,logmini)*(streets[n]);
	 		long 
	 		if (temp < mini) {
	 			mini = temp;
	 		}
	 		++i;
	 	}
	 	minimum[n] = mini;
	 	return minimum[n];
	 }
}

long long int compute () {
	long long int N,K;
	cin>>N>>K;
	vector<long long int> streets(N);
	vector<long long int> minimum(N,Max);
	for (int i=0; i<N; ++i) {
		cin>>streets[i];
	}
	minimum[0] = streets[0]%Max;
	return find_min(N-1,K,streets,minimum);
}

int main() {
	cout<<compute()%Max;
	return 0;
}