#include <iostream>
#include <string>
#include <vector>

using namespace std;

bool is_palin(string &s) {
	int left=0, right = s.length()-1;
	int mid = (left + right) / 2;
	for(int i=0; i<=mid; ++i) {
		if(s.at(left)!=s.at(right))
			return false;
		++left; --right;
	}
	return true;
}

int main() {
	int T;
	cin>>T;
	cin.get();
	vector<string> v(T);
	for(int t=0; t<T; ++t) {
		string s1,s2;
		getline(cin,s1);
		getline(cin,s2);
		int i=0;
		char c1 = s1.at(i);
		while(i<s1.length()) {
			c1 = s1.at(i);
			if(s2.find(c1)!=string::npos) {
				v[t] = "Yes";
				break;
			}
			++i;
		}
		if(i==s1.length()) {
			v[t]="No";
		}
	}
	for(int t=0; t<T; ++t)
		cout<<v[t]<<endl;
	return 0;
}