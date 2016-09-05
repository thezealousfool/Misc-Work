#include <iostream>
#include <vector>

using Int = long long int;

int main() {
	Int T, N;
	Int max = (Int)1E5;
	std::vector<Int> array(max);
	std::vector<Int> x((Int)(max * (max + 1) / 2.0));
	std::vector<Int> y((Int)(max * (max + 1) / 2.0));
	std::cin >> T;
	while (T--) {
		std::cin >> N;
		for (Int i = 0; i < N; ++i)
			std::cin >> array[i];

	}
	return 0;
}
