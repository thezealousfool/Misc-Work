#include <iostream>
#include <chrono>

int main() {
	auto N = int();
	std::ios::sync_with_stdio(false);
	std::cin >> N;
    std::cout << N << "\n";
	auto temp = int();
	auto start = std::chrono::steady_clock::now();
	for (auto i = 0; i < N; ++i) {
		std::cin >> temp;
	}
	auto end = std::chrono::steady_clock::now();
	auto time = end - start;
	std::cout << std::chrono::duration_cast<std::chrono::nanoseconds>(time).count() << "\n";
	return 0;
}
