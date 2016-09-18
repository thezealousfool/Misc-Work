#include <bits/stdc++.h>
using namespace std;

template <typename T>
T modular_exponentiation(T base, T power, T mod_base) {
	T result = 1;
	base = base % mod_base;

	while (power > 0) {
		if (power%2 == 1)
			result = (result * base) % mod_base;

		power /= 2;
		base = (base*base) % mod_base;
	}

	return result;
}

int main() {
	cout<<modular_exponentiation<int> (2,3,10)<<endl;
	return 0;
}