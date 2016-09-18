#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>

using Int = long long int;

int main() {
	std::ios::sync_with_stdio(false);
	Int N, W, L;
	Int result_time = 0;
	std::cin >> N >> W >> L;
	std::vector<Int> Hi (N);
	std::vector<Int> Ri (N);
	std::vector<Int> time_L (N);
	std::vector<Int> tree_name (N);
	for (Int i = 0; i < N; ++i) {
		std::cin >> Hi[i] >> Ri[i];
		if (Hi[i] < L)
			time_L[i] = ceil((L - Hi[i]) / (1.0*Ri[i]));
		else
			time_L[i] = 0;
		tree_name[i] = i;
	}
	std::sort(tree_name.begin(), tree_name.end(), [&time_L](auto& n1, auto& n2){
				return time_L[n2] > time_L[n1];
			});
	result_time += time_L[tree_name[0]];
	Int pos_tree = 1;
	Int present_value = -1 * W;
	Int rate = 0;
	for (Int i = 0; i < N && present_value < 0; ++i) {
		Int temp = Hi[i] + Ri[i] * result_time;
		if (temp >= L)
			present_value += temp;
	}
	if (present_value >= 0) {
		std::cout << result_time << "\n"; return 0;
	}
	while (present_value < 0) {
		if (pos_tree < N) {
			Int interval_time = time_L[tree_name[pos_tree]] - time_L[tree_name[pos_tree - 1]];
			rate += Ri[tree_name[pos_tree - 1]];
			if (present_value + rate * interval_time > 0) {
				result_time += ceil((-1.0 * present_value) / rate);
				std::cout << result_time << "\n";
				return 0;
			}
			present_value += time_L[tree_name[pos_tree]] * Ri[pos_tree] + Hi[pos_tree] + rate * interval_time;
			result_time += interval_time;
			++pos_tree;
		}
		else {
			rate += Ri[tree_name[pos_tree - 1]];
			result_time += ceil((-1.0 * present_value) / rate);
			std::cout << result_time << "\n";
			return 0;
		}
	}
	return 0;
}
