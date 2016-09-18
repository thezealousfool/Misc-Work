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
		size_t pos = inp.find(pat);
		cout<<pos<<endl;
		if(pos!=string::npos)
			output[i]="Yes";
		else
			output[i]="No";
	}
	for(int i=0; i<T; ++i) {
		cout<<output[i]<<endl;
	}
}