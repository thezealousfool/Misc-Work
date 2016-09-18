#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

void compute() {
	//bool b = false;
	int R,r,i;
	cout<<"Started\n";
	cin>>R>>i;
	cout<<R<<endl;
	vector<string> v_inp(R);
	for(i=0; i<R; ++i) {
		getline(cin,v_inp[i]);
		cin.get();
	}
	cin>>r>>i;
	cout<<r<<endl;
	vector<string> v_pat(r);
	for (i = 0; i < r; ++i)
	{
		getline(cin,v_pat[i]);
		cin.get();
	}
	cout<<endl;
	for_each(v_inp.begin(),v_inp.end(),[](string s){cout<<s<<endl;});
	cout<<endl;
	for_each(v_pat.begin(),v_pat.end(),[](string s){cout<<s<<endl;});
	//return b;
}

int main() {
	int n,i;
	cin>>n;
	vector<bool> v(n);
	for (i=0; i<n; ++i)
		compute();
	/*for (i=0; i<n; ++i)
		cout<<v[i]<<endl;*/
	return 0;
}
