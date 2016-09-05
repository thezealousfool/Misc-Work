/*input
2
aacaab
xxyx
*/
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

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
	int found_index = -1;
	for(int i=0; i<index && found_index==-1; ++i) {
		if(suffix[i+1]==suffix[i]+1)
			found_index = suffix[i];
	}
	int focus = index;
	while (found_index==-1)  {
		for(int i=0; i<index; ++i) {
			if(suffix[focus]-suffix[i]==1)
				found_index  = suffix[i];
		}
		++focus;
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