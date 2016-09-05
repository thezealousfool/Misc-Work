#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>

using Int = long long int;

int main() {
	std::ios::sync_with_stdio(false);
	Int N, W, L;
	Int result_time;
	std::cin >> N >> W >> L;
	std::vector<Int> Hi (N);
	std::vector<Int> Ri (N);
	std::vector<Int> time_L (N);
	std::vector<Int> tree_name (N);
	auto calculate_value = [&](Int time) {
		Int received = 0;
		for (Int i = 0; i < N; ++i) {
			Int temp = Hi[i] + (Ri[i] * time);
			if (temp >= L)
				received += temp;
			if (received >= W)
				break;
		}
		if (received > W)
			return 1;
		if (received < W)
			return -1;
		if (received == W)
			return 0;
	};
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
	Int loop_1 = 0;
	if (calculate_value(0) >= 0) {
		std::cout << "0" << "\n";
		return 0;
	}
	int temp = -1;
	Int loop_start = -1, loop_end = tree_name.size() - 1;
	loop_1 = (loop_start + loop_end) / 2;
	while (loop_1 < tree_name.size()) {
		result_time = time_L[tree_name[loop_1]];
		temp = calculate_value(result_time);
		if (temp > 0)
			loop_end = loop_1 - 1;
		else if (temp < 0)
			loop_start = loop_1 + 1;
		else
			break;
		if (loop_start >= loop_end)
			break;
		loop_1 = (loop_start + loop_end) / 2;
	}
	if (temp == 0) {
		std::cout << time_L[tree_name[loop_1]] << "\n";
		return 0;
	}
	if (temp < 0) {
		result_time = time_L[tree_name.back()] + 1;
		while (calculate_value(result_time) < 0) { ++result_time; }
		std::cout << result_time << "\n";
		return 0;
	}
	Int start, end, mid;
	if (loop_1 == 0) {
		std::cout << time_L[tree_name[0]] << "\n";
		return 0;
	}
	start = time_L[tree_name[loop_1 - 1]];
	end = time_L[tree_name[loop_1]];
	while (start <= end) {
		mid = (start + end) / 2;
		temp = calculate_value(mid);
		if (temp == 0) {
			std::cout << mid << "\n";
			return 0;
		}
		if (temp > 0) {
			if (calculate_value(mid - 1) < 0) {
				std::cout << mid << "\n";
				return 0;
			}
			if (calculate_value(mid - 1) == 0) {
				std::cout << mid - 1 << "\n";
				return 0;
			}
			else
				end = mid;
		}
		else {
			if (calculate_value(mid + 1) > 0) {
				std::cout << mid + 1 << "\n";
				return 0;
			}
			if (calculate_value(mid + 1) == 0) {
				std::cout << mid + 1 << "\n";
				return 0;
			}
			else
				start = mid;
		}
	}
}
