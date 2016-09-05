#include <iostream>
#include <vector>
#include <limits>

int main() {
	std::cout << std::numeric_limits<int>::max();
	std::vector<int> v;
	std::cout << "\n" << v.max_size() << "\n";
	return 0;
}