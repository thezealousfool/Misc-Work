#include <iostream>
#include <string>

int main() {
	int T, len;
	bool flag;
	std::cin >> T;
	std::string input;
	while (T--) {
		flag = true;
		std::cin >> input;
		len = input.length() - 1;
		int i = 0;
		while (i <= len) {
			if (input[i] == input[len]) {
				if (input[i] == '.')
					input[i] = input[len] = 'a';
			}
			else {
				if (input[i] == '.') {
					input[i] = input[len];
				}
				else if (input[len] == '.') {
					input[len] = input[i];
				}
				else {
					std::cout << "-1\n";
					flag = false;
				}
			}
			if (!flag)
				break;
			++i; --len;
		}
		if (flag)
			std::cout << input << "\n";
	}
	return 0;
}
