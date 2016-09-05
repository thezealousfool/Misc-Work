#include <iostream>
#include <algorithm>

using namespace std;

void compute() {
	int inp_len,pat_len;
	cin>>inp_len;
	vector<int> input(inp_len);
	for(int i=0; i<inp_len; ++i)
		cin>>input[i];
	sort(input.begin(),input.begin()+inp_len);
	cin>>pat_len;
	for(int i=0; i<pat_len; ++i) {
		int temp;
		cin>>temp;
		if(!binary_search(input.begin(),input.end(),temp)) {
			cout<<"No"<<endl;
			return;
		}
	}
	cout<<"Yes"<<endl;
	/*for(int i=0; i<inp_len; ++i)
		cout<<input[i]<<" ";*/
}

int main() {
	int T;
	cin>>T;
	while(T--)
		compute();
	return 0;
}