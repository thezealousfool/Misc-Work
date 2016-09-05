#include <iostream>
#include <vector>
#include <fstream>
#include <algorithm>
#include <chrono>

int main() {
	auto fin = std::fstream("input.txt", std::ios::in);
	auto fout = std::fstream("output.txt", std::ios::out);
	std::chrono::steady_clock::time_point start, end;
	std::chrono::steady_clock::duration time;
	int N;
	fin >> N;
	std::vector<int> input(N);
	std::vector<int> pq(N);
	std::vector<int> map(N);
	for (auto i = 0; i < input.size(); ++i) {
		fin >> input[i];
		pq[i] = i;
	}
	auto min = [&input, &pq, &map](const auto& i1, const auto& i2) {
			if (input[i2] < input[i1]) {
				std::swap(map[i2], map[i1]);
				return true;
			}
			return false;
		};

	start = std::chrono::steady_clock::now();
	std::make_heap(pq.begin(), pq.end(), min); 
	for (auto i = 0; i < map.size(); ++i) {
		map[pq[i]] = i;
	}

	while (pq.size() > 0) {
		std::pop_heap(pq.begin(), pq.end(), min); 
		map[pq.back()] = -1;
		fout << input[pq.back()] << " at " << pq.back() << "\n";
		pq.pop_back();
	}
	end = std::chrono::steady_clock::now();
	time = end-start;
	std::cout << std::chrono::duration_cast<std::chrono::milliseconds>(time).count() << "\n";
	std::cout.flush();
	return 0;
}
