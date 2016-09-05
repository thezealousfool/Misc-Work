#include <iostream>
#include <set>
#include <vector>
#include <algorithm>

using namespace std;

typedef long long int Int;

int main() {
	Int N;
	cin>>N;
	vector<Int> Inp(2*N);
	//cout<<Inp.size();
	Int min_element, max_element;
	cin>>Inp[0];
	min_element = max_element = Inp[0];
	for(Int i=1; i<2*N; ++i) {
		cin>>Inp[i];
		if(Inp[i] < min_element)
			min_element = Inp[i];
		if(Inp[i] > max_element)
			max_element = Inp[i];
	}
	Int size_vector = max_element - min_element + 1;
	//cout<<size_vector<<endl;
	vector< set<int> > v(size_vector);
	//cout<<v.size()<<endl;
	for (Int i=0; i<2*N; i+=2) {
		for(Int j=Inp[i]; j<=Inp[i+1]; ++j)
			v[j-1].insert(i/2 + 1);
	}
	Int T;
	cin>>T;
	for(Int i=0; i<T; ++i) {
		Int k;
		set<Int> result;
		cin>>k;
		for(Int j=0; j<k; ++j) {
			Int index;
			cin>>index;
			--index;
			for_each(v[index].begin(),v[index].end(),[&result](Int elem){result.insert(elem);});
		}
		cout<<result.size()<<endl;
	}
	return 0;
}