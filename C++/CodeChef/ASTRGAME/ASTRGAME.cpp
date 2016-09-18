#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

int main() {
	int T;
	int N;
	std::string full_text;
	std::vector <std::string> dict(30);
	std::cin >> T;
	int found;
	std::vector <std::string> result(T);
	while (T--) {
		found = 0;
		std::cin >> full_text >> N;
		std::size_t pos_found;
		for (int i = 0; i < N; ++i) {
			std::cin >> dict[i];
			pos_found = full_text.find(dict[i]);
			if (pos_found != std::string::npos) {
				++found; full_text.replace(pos_found, dict[i].size(), "*");
			}
		}
		if (found & 1)
			result[T] = "Teddy\n";
		else
			result[T] = "Tracy\n";
	}
	std::for_each(result.crbegin(), result.crend(), [](const std::string s1) {std::cout << s1;});
	return 0;
}
