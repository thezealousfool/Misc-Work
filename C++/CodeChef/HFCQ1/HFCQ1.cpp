/*input
4
xy
aaa
xxyx
a
*/
#include <iostream>
#include <string>
#include <cmath>

using namespace std;

int main() {
	int T;
	cin>>T;
	cin.get();
	while(T--) {
		string s;
		getline(cin,s);
		int count = 0;
		if(s.length()==1){
			cout<<2<<endl;
			continue;
		}
		if(s.at(0)!=s.at(1))
			++count;
		int i;
		for(i=1; i<s.length()-1; ++i) {
			if(s.at(i-1) != s.at(i) && s.at(i) != s.at(i+1))
				++count;
		}
		if(s.at(s.length()-1)!=s.at(s.length()-2))
			++count;
		cout<<(int)(pow(2,count))<<endl;
	}
	return 0;
}