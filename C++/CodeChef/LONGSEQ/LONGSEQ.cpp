#include <iostream>
#include <vector>

int main() {
	int T, no_zero, no_one;
	char input;
	std::cin >> T;
	getchar();
	while (T--) {
		no_one = no_zero = 0;
		do {
			input = getchar();
			if (input == '0')
				++no_zero;
			else if (input == '1')
				++no_one;
		} while (input != '\n');
		if (no_one == 1 || no_zero == 1) {
			std::cout << "Yes\n";
		}
		else {
			std::cout << "No\n";
		}
	}
	return 0;
}
