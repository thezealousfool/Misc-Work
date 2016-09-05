#include <iostream>
#include <deque>
#include <algorithm>
using namespace std;
int main() {
	deque <char> inp1,inp2;
	int count = 0;
	char t1,t2,k = cin.get();
	bool b = true;
	while (k!='\n') {
		inp1.push_back(k);
		k = cin.get();
	}
	k = cin.get();
	while (k!='\n') {
		inp2.push_back(k);
		k = cin.get();
	}
	//cout<<endl;
	sort(inp1.begin(),inp1.end());
	sort(inp2.begin(),inp2.end());
	/*cout<<"Input1: ";
	for_each(inp1.begin(),inp1.end(),[](char ch){cout<<ch<<" ";});
	cout<<endl<<"Input2: ";
	for_each(inp2.begin(),inp2.end(),[](char ch){cout<<ch<<" ";});
	cout<<endl;*/
	while (b) {
		//cout<<"count: "<<count<<"\tinp1: "<<inp1.size()<<"\tinp2: "<<inp2.size()<<endl;
		if (inp1.size()==0) {
			count += inp2.size();
			b = false;
			continue;
		}
		else if (inp2.size()==0) {
			count += inp1.size();
			b = false;
			continue;
		}
		t1 = inp1.front();
		t2 = inp2.front();
		if(t1!=t2){
			count++;
			if (t1<t2) {
				//cout<<"popping "<<t1<<endl;
				inp1.pop_front();
			}
			else {
				//cout<<"popping "<<t2<<endl;
				inp2.pop_front();
			}
		}
		else {
			inp1.pop_front();
			inp2.pop_front();
			//cout<<"popping "<<t1<<" and "<<t2<<endl;
		}
	}
	cout<<count;
    return 0;
}