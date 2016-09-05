#include <iostream>
#include <fstream>
#include <chrono>
#include <vector>

void bubble_sort(std::vector<int>& array) {
	for (int i = 0; i < array.size(); ++i) {
		for (int j = 0; j < array.size() - 1; ++j) {
			if (array[j] > array[j+1]) {
				int temp = array[j+1];
				array[j+1] = array[j];
				array[j] = temp;
			}
		}
	}
}

void shuffle(std::vector<int>& array) {
	for (int i = array.size() - 1; i > 0; --i) {
		int temp = rand() % i;
		int atemp = array[temp];
		array[temp] = array[i];
		array[i] = atemp;
	}
}

int main() {
	std::vector<int> array;
	int iterations;
	auto file = std::fstream("time.dat", std::ios::out);
	std::cout << "No of iterations? ";
	std::cin >> iterations;
	while (iterations--) {
		std::cout << "Adding 10 elements...\n";
		array.reserve(array.size() + 10);
		for (int i = 0; i < 10; ++i) {
			array.push_back(rand() % (array.size() + 20));
		}
		shuffle(array);
		auto start = std::chrono::steady_clock::now();
		bubble_sort(array);
		auto end = std::chrono::steady_clock::now();
		auto time = end - start;
		std::cout << "Time: " << std::chrono::duration_cast<std::chrono::nanoseconds>(time).count() << "nanoseconds\n";
		file << array.size() << " " << std::chrono::duration_cast<std::chrono::nanoseconds>(time).count() << "\n";
	}
	return 0;
}
