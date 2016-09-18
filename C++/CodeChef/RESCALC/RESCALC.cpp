#include <iostream>
#include <vector>

int main() {
	int T, people, temp, temp2, types, scores, max_score_index, max_score = 0;
	bool flag = true;
	std::vector<int> quantity(6);
	std::cin >> T;
	while (T--) {
		max_score = 0;
		flag = true;
		std::cin >> people;

		for (int i = 0; i < people; ++i) {
			scores = 0;
			for (int i = 0; i < 6; ++i) {
				quantity[i] = 0;
			}
			std::cin >> temp;
			for (int j = 0; j < temp; ++j) {
				std::cin >> temp2;
				++quantity[temp2 - 1];
			}
			while (temp) {
				types = 0;
				for (int j = 0; j < 6; ++j) {
					if (quantity[j]) {
						++scores;
						++types;
						--temp;
						--quantity[j];
					}
				}
				switch (types) {
					case 4: scores += 1; break;
					case 5: scores += 2; break;
					case 6: scores += 4; break;
				}
			}
			if (scores > max_score) {
				max_score_index = i+1;
				flag = true;
				max_score = scores;
			}
			else if (scores == max_score)
				flag = false;
		}

		if (!flag) 
			std::cout << "tie\n";
		else if (max_score_index == 1)
			std::cout << "chef\n";
		else
			std::cout << max_score_index << "\n";
	}
	return 0;
}
