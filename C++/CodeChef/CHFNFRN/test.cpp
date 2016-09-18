#include <iostream>
#include <vector>

int main() {
	std::vector<int> v(10);
	for (int i = 0; i < 10; ++i) {
		v[i] = i+1;
	}
	std::cout << "before:\n";
	for (const auto& e : v) {
		std::cout << e << "  ";
	}
	std::cout << "\n\n";
	for (int i = 0; i < 10; ++i) {
		if (i)
	}
}