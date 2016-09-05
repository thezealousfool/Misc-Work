#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

struct Node {
	int position;
	int value;
};

int main() {
	auto min = [](const Node& n1,const Node& n2){return n2.value<n1.value;};
	vector<Node> v(0);
	int value;
	for(int i=0; i<5; ++i) {
		cin>>value;
		Node n = {i,value};
		v.push_back(n);
		push_heap(v.begin(),v.end(),min);
	}
	cout<<endl;
	while(v.size()!=0) {
		cout<<v.front().position<<"\t"<<v.front().value<<endl;
		pop_heap(v.begin(),v.end(),min);
		v.pop_back();
	}
}