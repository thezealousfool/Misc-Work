#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

typedef long long int Int;
const Int Mod = (Int)1E9 + 7;
Int N,sum;

void Return (Int T, Int &CRM) {
	if (T<0)
		return;
	else {
		Return(T-1,CRM);
		CRM = (Int)(pow(N-1,T)*sum - CRM);
		while(CRM < 0)
			CRM += Mod;
		CRM %= Mod;
	}
}

int main() {
	cin>>N;
	vector<Int> CRM(N);
	for(Int i=0; i<N; ++i) {
		cin>>CRM[i];
		sum += CRM[i];
	}
	Int T;
	cin>>T;
	Int Q;
	cin>>Q;
	for(Int i=1; i<N; ++i) {
		CRM[i] -= CRM[0];
	}
	Return(T-1,CRM[0]);
	for(Int i=0; i<Q; ++i) {
		Int index;
		cin>>index;
		if(index!=1)
			cout<<(Int)(CRM[0]+pow(-1,T)*CRM[index-1])<<endl;
		else
			cout<<CRM[0]<<endl;
	}
	return 0;
}