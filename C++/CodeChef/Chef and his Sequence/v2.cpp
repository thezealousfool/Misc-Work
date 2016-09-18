#include <iostream>
#include <string>
#include <vector>

using namespace std;

int main() {
	int T;
	cin>>T;
	vector<string> output(T);
	for(int i=0; i<T; ++i) {
		int temp;
		cin>>temp;
		cin.get();
		string inp,pat;
		getline(cin,inp);
		cin>>temp;
		cin.get();
		getline(cin,pat);
		bool flag = false;
		int k;
		for(k=0; k<=(inp.size()-pat.size()); ++k) {
			string tmp = inp.substr(k,pat.size());
			if(tmp==pat) {
				flag=true;
				break;
			}
		}
		if(flag)
			output[i]="Yes";
		else
			output[i]="No";
	}
	for(int i=0; i<T; ++i) {
		cout<<output[i]<<endl;
	}
}