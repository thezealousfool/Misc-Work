#include <iostream>
#include <vector>
#include <cmath>

using Int = long long int;

int main() {
	std::ios::sync_with_stdio(false);
	Int N, W, L;
	Int min_tree_L = 1E18 + 5;
	std::cin >> N >> W >> L;
	std::vector<Int> Hi (N);
	std::vector<Int> Ri (N);
	auto calculate_value = [&](Int time) {
		Int received = 0;
		for (Int i = 0; i < N; ++i) {
			Int temp = Hi[i] + (Ri[i] * time);
			if (temp < L)
				continue;
			if (received >= W - temp)
				return 1;
			if (received < W - temp)
				received += temp;
		}
		return -1;
	};
	for (Int i = 0; i < N; ++i) {
		std::cin >> Hi[i] >> Ri[i];
		Int temp_L = ceil((L - Hi[i])/(1.0 * Ri[i]));
		if (temp_L < min_tree_L)
			min_tree_L = temp_L;
	}
	Int start = -1, end = 1E18 + 5, mid;
	mid = (start + end) / 2;
	while ((start + 1) < end) {
		int temp = calculate_value(mid);
		if (temp >= 0)
			end = mid;
		else
			start = mid;
		mid = (start + end) / 2;
	}
	if (end < min_tree_L)
		end = min_tree_L;
	std::cout << end << "\n";
	return 0;
}	
