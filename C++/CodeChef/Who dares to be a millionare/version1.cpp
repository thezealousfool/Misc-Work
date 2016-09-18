#include <iostream>
#include <array>
#include <string>

using namespace std;

typedef long long int Int;

array<Int, 1002> winnings;
array<Int, 501> output;


Int compute() {
	Int N;
	cin>>N;
	cin.get();
	string chef, quiz;
	getline(cin,chef);
	getline(cin,quiz);
	Int i;
	for(i = 0; i<=N; ++i) {
		cin>>winnings[i];
	}
	Int k = 0;
	for (i = 0; i<N; ++i) {
		if (chef.at(i)==quiz.at(i))
			++k;
	}
	if(k!=N) {
		Int max = 0;
		for (i = 0; i<=k; ++i) {
			if (max<winnings[i])
				max = winnings[i];
		}
		return max;
	}
	else {
		return winnings[N];
	}
}
int main() {
	int T;
	cin>>T;
	for (int i = 0; i<T; ++i) {
		output[i]=compute();
	}
	for (int i = 0; i<T; ++i){
		cout<<output[i]<<endl;
	}
	return 0;
}