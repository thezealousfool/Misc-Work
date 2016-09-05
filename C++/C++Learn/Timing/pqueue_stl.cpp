#include <iostream>
#include <algorithm>
#include <vector>
#include <fstream>
#include <chrono>
#include <iterator>

int main() {
	// auto fin = std::fstream("input.txt", std::ios::in);
	// auto fout = std::fstream("output.txt", std::ios::out);
	// int n = 40100;
	// std::vector<int> pq(n);
	// std::vector<int> map(n);
	// std::vector<int> r_map(n);
	std::vector<int> pq = {13, 7, 17, 22, 10, 9, 1, 3, 2, 5, 6};
	std::vector<int> map(pq.size());
	std::vector<int> r_map(pq.size());
	for (auto i = 0; i < pq.size(); ++i) {
		// fin >> pq[i];
		map[i] = i;
		r_map[i] = i;
	}
	for (auto& e : pq)
		std::cout << e << " ";
	std::cout << "\n";
	for (auto& e : map)
		std::cout << e << " ";
	std::cout << "\n";
	for (auto& e : r_map)
		std::cout << e << " ";
	std::cout << "\n";
	auto start = std::chrono::steady_clock::now();
	std::make_heap(pq.begin(), pq.end(), [&pq, &map, &r_map](auto& i1, auto& i2) { if(i1 > i2) {
			std::swap(map[(&i1 - &pq.front())], map[(&i2 - &pq.front())]);
			std::swap(r_map[map[(&i1 - &pq.front())]], r_map[map[(&i2 - &pq.front())]]);
			return false;
		}
		return true; });
	for (auto& e : pq)
		std::cout << e << " ";
	std::cout << "\n";
	for (auto& e : map)
		std::cout << e << " ";
	std::cout << "\n";
	for (auto& e : r_map)
		std::cout << e << " ";
	std::cout << "\n";
	return 0;
}
