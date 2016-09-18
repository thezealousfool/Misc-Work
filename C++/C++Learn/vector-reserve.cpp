#include <iostream>
#include <vector>

using namespace std;

int main() {
	vector<int> v;
	v.reserve(100);
	cout<<v.size()<<"\t"<<v.capacity()<<endl;
	v.push_back(1);
	cout<<v.size()<<"\t"<<v.capacity()<<endl;
	return 0;
}