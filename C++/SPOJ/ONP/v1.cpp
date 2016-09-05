/*input
1
(a+b)/c
*/
#include <iostream>
#include <vector>
#include <string>
#include <stack>

using namespace std;

int main() {
	int T;
	cin>>T;
	cin.get();
	while(T--) {
		string s;
		getline(cin,s);
		s += ")";
		stack<char> sk;
		sk.push('(');
		for(int i=0; i<s.length(); ++i) {
			char c = s.at(i);
			if((c>='a' && c<='z') || (c>='A' && c<='Z'))
				cout<<c;
			else if(c=='(')
				sk.push('(');
			else if(c==')') {
				c = sk.top();
				sk.pop();
				while(c != '(') {
					cout<<c;
					c = sk.top();
					sk.pop();
				}
			}
			else
				sk.push(c);
		}
		cout<<endl;
	}
	return 0;
}