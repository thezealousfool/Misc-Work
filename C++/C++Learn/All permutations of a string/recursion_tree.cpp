#include <iostream>
#include <vector>
#include <string>
#include <functional>

void all_permutations (std::string& s) {

	auto swap = [] (char& c1, char&c2) {

		char temp = c1;
		c1 = c2;
		c2 = temp;
	};

	std::function<void (int)> permutate = [&s, &swap, &permutate] (int N) {
		if (N==s.length()-1) {
			// change this block if you want to do something else
			// with the different permutations obtained rather than just print it.
			std::cout << s << std::endl;
			return;
		}
		for (int i = N; i<s.length(); ++i) {
			swap (s[i], s[N]);
			permutate (N+1);
			swap (s[i], s[N]);
		}
	};

	permutate (0);
}

int main() {
	std::string s = "ABC";
	all_permutations (s);
	return 0;
}