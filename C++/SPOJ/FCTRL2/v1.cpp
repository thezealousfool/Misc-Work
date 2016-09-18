/*input
1
500
*/
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;


void product (const int& i, vector<short int> &v) {
	int carry = 0;
	auto pos = v.begin();
	int tmp = 1;
	while (pos!=v.end() || carry!=0) {
		if(pos==v.end()){
			v.push_back(0);
			pos = --v.end();
		}
		tmp = *pos * i + carry;
		*pos = tmp % 10;
		carry = tmp / 10;
		++pos;
	}
}

void compute() {
    vector<short int> v{};
	v.push_back(1);
    int input;
    cin>>input;
    while (input>1) {
    	product(input,v);
    	--input;
    }
    for_each(v.crbegin(),v.crend(),[](int x){cout<<x;});
    cout<<endl;
    cout<<"Digits: "<<v.size()<<endl;
}

int main() {
    int T;
    cin>>T;
    for(int t=0; t<T; ++t) {
        compute();
    }
}