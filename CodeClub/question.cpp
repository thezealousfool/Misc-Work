#include <iostream>
#include <fstream>

int fun (int n) {
	int count = 0;
	for (int i = n; i > 0; i /= 2)
		for (int j = 0; j < i; ++j)
			++count;
	return count;
}

int main() {
	auto file = std::fstream("time.dat", std::ios::out);
	std::cout << "No of iterations? ";
	int iterations;
	std::cin >> iterations;
	for (int i = 0; iterations--; i+=10) {
		file << i << " " << fun(i) << "\n";
	}
	std::cout << "Done!\n";
	return 0;
}
