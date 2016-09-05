#include <iostream>
#include <string>
#include <vector>

using namespace std;

bool compute() {
	string S;
	getline(cin,S);
	int len = S.length();
	for (int i = 1,j = len-i; i<len; ++i){
		j=len-i;
		if(abs(S.at(i)-S.at(i-1)) != abs(S.at(j-1)-S.at(j))) {
			return false;
		}
	}
	return true;
}

int main() {
	int n,i;
	cin>>n;
	cin.get();
	vector<bool> v(n);
	for (i=0; i<n; ++i)
		v[i] = compute();
	for (i=0; i<n; ++i) {
		if (v[i])
			cout<<"Funny"<<endl;
		else
			cout<<"Not Funny"<<endl;
	}
}