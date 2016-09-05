/*input
30000
*/
#include <vector>
#include <iostream>
#include <algorithm>
#define max 122000
using namespace std;

vector<short int> v{};

void product (const int& i) {
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

int main() {
    v.reserve(max);
    v.push_back(1);
    int input;
    cout<<"Number: ";
    cin>>input;
    while (input>1) {
    	product(input);
    	--input;
    }
    /*for (auto ele = v.crbegin(); ele != v.crend(); ++ele) {
        cout<<*ele;
    }
    cout<<endl;*/
    for_each(v.crbegin(),v.crend(),[](int x){cout<<x;});
    cout<<endl;
    cout<<"Digits: "<<v.size()<<endl;
    //cout<<"Maximum size: "<<v.max_size()<<endl;
    return 0;
}
