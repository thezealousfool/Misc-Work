#include <iostream>
#include <string>
#include <cstdio>

using namespace std;
typedef long long int Int;

bool check(const string &s1,const string &s2) {
	if(s1.length()!=s2.length())
		return false;
	for(int i=0; i<s1.length(); ++i) {
		if(s1.at(i) != s2.at(i))
			return false;
	}
	return true;
}

int main() {
	Int T,left,right;
	cin>>T;
	cin.get();
	string s,s1;
	while(T--) {
		cin>>s;
		if(s.length()%2==0) {
			if(check(string(s.begin(),s.begin()+s.length()/2),string(s.begin()+s.length()/2, s.end())))
				cout<<"YES"<<endl;
			else
				cout<<"NO"<<endl;
		}
		else {
			left = 0; right = s.length()/2 + 1;
			s1 = s;
			while(right<s.length() && s.at(left)==s.at(right)) {
				++left; ++right;
			}
			if(right==s.length()) {
				cout<<"YES"<<endl; continue;
			}
			if(s.at(left+1)==s.at(right)) {
				s.erase(left,1);
			}
			if(check(string(s.begin(),s.begin()+s.length()/2),string(s.begin()+s.length()/2, s.end()))) {
				cout<<"YES"<<endl; continue;
			}
			left = 0; right = s1.length()/2;
			while(right<s1.length() && s1.at(left)==s1.at(right)) {
				++left; ++right;
			}
			if(right>=s1.length()-1) {
				cout<<"YES"<<endl; continue;
			}
			if(s1.at(left)==s1.at(right+1)) {
				s1.erase(right,1);
			}
			if(check(string(s1.begin(),s1.begin()+s1.length()/2),string(s1.begin()+s1.length()/2, s1.end()))) {
				cout<<"YES"<<endl; continue;
			}
			cout<<"NO"<<endl;
		}
	}
	return 0;
}