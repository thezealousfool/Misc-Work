#include <algorithm>
#include <iostream>
#include <fstream>
#include <chrono>
#include <string>
#include <vector>

bool linear_word_search (const std::vector<std::string>& list, const std::string& word) {
	for (auto& w : list)
		if (word == w)
			return true;
	return false;
}

int main() {
	auto file = std::fstream("time.dat", std::ios::out);
	std::vector<std::string> word_list;
	auto random_string = [](int size) {
		auto rand_char = []() {
			return (char)((std::rand())%(123-97) + 97);
		};
		std::string s;
		std::generate_n(s.begin(), size, rand_char);
		return s;
	};
	std::string word;
	std::cout << "Word to be searched? ";
	std::cin >> word;
	std::cout << "No of iterations? ";
	int iterations;
	std::cin >> iterations;
	while (iterations--) {
		std::cout << "Adding 10 elements...\n";
		word_list.reserve(word_list.size() + 10);
		for (int i = 0; i < 10; ++i) {
			word_list.push_back(random_string(30));
		}
		auto start = std::chrono::steady_clock::now();
		if (linear_word_search(word_list, word)) {
			std::cout << "Found\n";
		}
		else {
			std::cout << "Not Found\n";
		}
		auto end = std::chrono::steady_clock::now();
		auto time = end - start;
		std::cout << "Time: " << std::chrono::duration_cast<std::chrono::nanoseconds>(time).count() << " nanoseconds\n\n";
		file << word_list.size() << " " << std::chrono::duration_cast<std::chrono::nanoseconds>(time).count() << "\n";
	}
	return 0;
}
