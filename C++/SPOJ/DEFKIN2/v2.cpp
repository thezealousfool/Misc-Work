#include <iostream>
#include <cmath>
#include <vector>
using namespace std;

int main() {
	int T;
	cin>>T;
	vector<int> res(T);
	for(int i=0; i<T; ++i) {
		int row,column,elements;
		cin>>row>>column>>elements;
		res[i] = ceil(((double)(row-elements))/(elements+1)) * ceil(((double)(column-elements))/(elements+1));
	}
	for(int i=0; i<T; ++i) {
		cout<<res[i]<<endl;
	}
	return 0;
}