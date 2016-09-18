/*input
120387
*/

#include <bits/stdc++.h>
using namespace std;

bool is_prime(int number) {
	if (number<=1) {
		return false;
	}
	if(number<=3) {
		return true;
	}
	if(number%2==0 || number%3==0) {
		return false;
	}
	for(int i=5; i*i<=number; i += 6) {
		if(number%i==0 || number%(i+2)==0)
			return false;
	}
	return true;
}

int main() {
	for (int i=2; i<1000; ++i)
		if (is_prime(i))
			cout<<i<<" ";
	cout<<endl;
	return 0;
}