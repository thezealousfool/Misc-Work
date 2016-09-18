#include <iostream>
#include <string>

using namespace std;

typedef long long int Int;

void compute() {
	Int sum=0;
	Int max_sum=0;
	string input;
	getline(cin,input);
	for(Int i=0; i<input.size(); ++i) {
		if(input[i]=='(')
			++sum;
		else {
			max_sum = sum>max_sum?sum:max_sum;
			--sum;
		}
	}
	for(Int i=0; i<max_sum; ++i)
		cout<<"(";
	for(Int i=0; i<max_sum; ++i)
		cout<<")";
	cout<<endl;
}

int main() {
	int T;
	cin>>T;
	cin.get();
	for(int i=0; i<T; ++i)
		compute();
	return 0;
}