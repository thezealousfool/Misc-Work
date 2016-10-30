#include <iostream>

std::size_t find_zero(const std::string& s) {
	std::size_t i = s.length() - 1;
	for (auto itr = s.crbegin(); itr != s.crend(); ++itr) {
		if((*itr) == '0')
			return i;
		else
			--i;
	}
	return i;
}

std::size_t count_ones(const std::string& s) {
	std::size_t i = 0;
	for (auto itr = s.cbegin(); itr != s.cend(); ++itr) {
		if ((*itr) == '1')
			++i;
	}
	return i;
}

std::size_t count_ones(const std::string& s, std::size_t till) {
	std::size_t res = 0;
	for(std::size_t i = 0; i <= till; ++i) {
		if (s[i] == '1')
			++res;
	}
	return res;
}

int main() {
	std::ios_base::sync_with_stdio(false);

	int T;
	std::size_t res, no, head_z, body_z, foot_z;
	std::string head, body, foot;

	std::cin >> T;

	while(T--) {
		no = 0;
		res = 0;
		head_z = body_z = foot_z = 0;

		std::cin >> head >> body >> foot;
		std::cin >> no;

		if (foot_z = find_zero(foot) == -1) {
			if ((no <= 0) || (body_z = find_zero(body) == -1)) {
				if (head_z = find_zero(head) == -1) {
					std::cout << 1 << "\n";
				}
				else {
					std::cout << count_ones(head, head_z) + 1 << "\n";
				}
			}
			else {
				std::cout << count_ones(head) + count_ones(body)*(no-1) + count_ones(body, body_z) + count_ones(foot) + 1 << "\n";
			}
		}
		else {
			std::cout << count_ones(head) + count_ones(body)*(no) + count_ones(foot, foot_z) + 1 << "\n";
		}
	}
	return 0;
}
