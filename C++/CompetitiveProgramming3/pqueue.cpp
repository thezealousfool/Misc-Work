#include <iostream>
#include <vector>
#include <algorithm>

int main() {
	
	// creating containers
	std::vector<int> v = {13,3,7,9,2,6,1,10,17,22,5};
	std::vector<int> map(v.size());
	std::vector<int> reverse_map(v.size());

	// initializing containers
       	for (auto i = 0; i < map.size(); ++i) {
		reverse_map[i] = i;
		map[i] = i;
	}

	// for (auto& e : v)
		// std::cout << e << " ";
	// std::cout << "\n";


	// make_heap
	std::make_heap(map.begin(), map.end(), [&v](auto& i1, auto& i2) { return v[i1] > v[i2]; });
	std::make_heap(v.begin(), v.end(), [](auto& i1, auto& i2) { return i1 > i2; });
       	for (auto i = 0; i < map.size(); ++i) {
		reverse_map[map[i]] = i;
	}

	// pop_heap
	std::pop_heap(map.begin(), map.end(), [&v](auto& i1, auto& i2) { return v[i1] > v[i2]; });
	std::pop_heap(v.begin(), v.end(), [](auto& i1, auto& i2) { return i1 > i2; });
	reverse_map[map.back()] = -1;
	v.pop_back();
	map.pop_back();
       	for (auto i = 0; i < map.size(); ++i) {
		reverse_map[map[i]] = i;
	}

	// print
	// for (auto& e : v)
	// 	std::cout << e << " ";
	// std::cout << "\n";
	// for (auto& e : map)
 	// 	std::cout << e << " ";
 	// std::cout << "\n";
 	// for (auto& e : reverse_map)
 		// std::cout << e << " ";
	// std::cout << "\n";
	return 0;
}
