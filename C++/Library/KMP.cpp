#include <iostream>
#include <vector>
#include <string>

auto populate_kmp_values (std::string text) {
	std::vector<int> values(text.length());
	values[0] = 0;
	int i = 0, j = 0;
	for (i = 1; i < values.size(); ++i) {
		if (text[i] == text[j]) {
			values[i] = j+1;
			++i; ++j;
		}
		else {
			j = values[j];
			--i;
		}
	}
	return values;
}

int main() {
	std::string text = "Hello world my name is hello how are you hello";
	std::string word = "hello";
	auto values = populate_kmp_values(text);
	for (const auto& e : text) {
		std::cout << e << " ";
	}
	std::cout << "\n";
	for (const auto& e : values) {
		std::cout << e << " ";
	}
	std::cout << "\n";
	return 0;
}