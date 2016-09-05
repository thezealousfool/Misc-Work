/*input
2
abacab
xxyx
*/
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

int lex(const string &s, int len, int i1, int i2) {
	if(i1>=s.length() || i2>=s.length())
		return -1;
	string s1 (s,i1,len);
	string s2 (s+s,i2,len);
	return s1.compare(s2)<0?i1:i2;
}

int lexicographically_smallest_circular_string(string &s) {
	int len = s.length();
	s = s+s;
	vector<int> suffix(len+1);
	for(int i=0; i<len+1; ++i)
		suffix[i] = i;
	sort(suffix.begin(), suffix.end(), [&s](int i, int j){
		return s[j] > s[i];
	});
	int index = 1;
	while(index<len) {
		if(s[suffix[index]]==s[suffix[index-1]])
			++index;
		else
			break;
	}
	int found_index = suffix[0];
	for(int i=1; i<index; ++i) {
		found_index = lex(s, len, found_index, suffix[i]);
	}
	for(int i=0; i<len; ++i)
		cout<<s[found_index+i];
	cout<<endl;
}

int main() {
	int T;
	cin>>T;
	cin.get();
	vector<int> results(T);
	for(int t=0; t<T; ++t) {
		string s;
		getline(cin,s);
		if(s.length()==1) {
			results[t] = 1;
			continue;
		}
		lexicographically_smallest_circular_string(s);
	}	
	return 0;
}