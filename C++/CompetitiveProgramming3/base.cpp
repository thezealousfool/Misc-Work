#include <iostream>
#include <iomanip>

int main() {
	auto X = 10, Y = 10;
	auto S = 1;
	std::cin >> X;
	std::cin >> std::setbase(X) >> S;
	std::cin >> std::setbase(10);
	std::cin >> Y;
	std::cout << std::setbase(Y) << S << "\n";
	return 0;
}
