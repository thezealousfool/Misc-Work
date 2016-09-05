/*input
*/
#include <iostream>
#include <vector>
#include <algorithm>

typedef long long int Int;

Int order_of_prime(Int number, Int prime) {
	/*
	calculate the power of a prime present
	in the factorial of a number.

	arguments:
	number : factorial to be searched
	prime : prime to be counted
	*/
	Int count = 0;
	while(number>0) {
		number /= prime;
		count += number;
	}
	return count;
}

std::vector<int> factorial(int number) {
	/*
	calculate factorial of a big number and
	return a int vector representing
	its digits.

	arguments:
	number : whose factorial is to be calculated
	*/
	std::vector<int> digits;
	digits.push_back(1);
	int carry, tmp;
	std::vector<int>::iterator pos = digits.begin();
	while (number>1) {
		carry = 0;
		pos = digits.begin();
		tmp = 1;
		while (pos!=digits.end() || carry!=0) {
			if(pos==digits.end()){
				digits.push_back(0);
				pos = --digits.end();
			}
			tmp = *pos * number + carry;
			*pos = tmp % 10;
			carry = tmp / 10;
			++pos;
		}
		--number;
	}
	reverse(digits.begin(),digits.end());
	return digits;
}

int main() {
	return 0;
}