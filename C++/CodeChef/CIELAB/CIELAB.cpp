#include <iostream>

int main() {
	int A, B;
	std::cin >> A >> B;
	int C = A-B;
	if (C%10 == 9)
		--C;
	else
		++C;
	std::cout << C << "\n";
	return 0;
}
