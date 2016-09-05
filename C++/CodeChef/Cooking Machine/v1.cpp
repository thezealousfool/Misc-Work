#include <iostream>
#include <cmath>
#include <vector>

using namespace std;
typedef long long int Int;
int main() {
	int T;
	cin>>T;
	vector<int> output(T);
	for(int i=0; i<T; ++i) {
		Int A,B;
		int count = 0;
		cin>>A>>B;
		while(log2(A)!=(float)((int)(log2(A)))) {
			A=A>>1;
			++count;
		}
		count += (int)(abs(log2(B)-log2(A)));
		output[i] = count;
	}
	for(int i=0; i<T; ++i) {
		cout<<output[i]<<endl;
	}
	return 0;
}