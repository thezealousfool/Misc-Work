#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

typedef long long int Int;
typedef long double Dob;

static Int N,K;
const Int Mod = (Int)1E9 + 7;
const Int log_max = (Int)1E6;
vector<Int> path(0);

Dob find_min(Int n, vector<Int>& streets, vector<Dob>& logs) {
	Int pos;
	Dob temp;
	if (logs[n]!=log_max) {
		return logs[n];
	}
	else {
		temp = find_min(n-1,streets,logs);
		pos = -1;
		Int k = 1;
		while (k<=K && n-k>=0) {
			Dob new_tmp = find_min(n-k,streets,logs);
			if(new_tmp<temp) {
				temp = new_tmp;
				pos = n-k;
			}
			++k;
		}
	}
	if (pos!=-1)
		path.push_back(pos);
	return temp+log10(streets[n]);
}


int main() {
	cin>>N>>K;
	vector<Int> streets(N);
	vector<Dob> logs(N,log_max);
	for(Int i=0; i<N; ++i) {
		cin>>streets[i];
	}
	logs[0] = log10(streets[0]);
	//path.push_back(0);
	find_min(N-1,streets,logs);
	//path.push_back(N-1);
	Int ans=1;
	for_each(path.begin(),path.end(),[](Int pos){cout<<pos<<endl;});
	//for_each(path.begin(),path.end(),[&](Int pos){ans*=streets[pos];ans%=Mod;});
	cout<<ans;
	return 0;
}