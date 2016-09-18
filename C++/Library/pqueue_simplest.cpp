#include <iostream>
#include <vector>
#include <algorithm>
#include <iomanip>

int main() {

	// "input" should be a map from some identification value to the priority weights value
	// "pq" should be an array (vector) of the identification values
	// "map" should be a map from the identification values to the index (position) of that value in 'pq'

	std::vector<int> input = {13, 7, 17, 22, 10, 9, 1, 3, 2, 5, 6};
	std::vector<int> map(input.size());
	std::vector<int> pq(input.size());
	for (auto i = 0; i < input.size(); ++i) 
		pq[i] = i;

	auto min = [&input, &map](const auto& i1, const auto& i2) { 
		if (input[i2] < input[i1]) {
			std::swap(map[i2], map[i1]);
			return true;
		}
		return false;
	};
	
	
	// make_heap
	std::make_heap(pq.begin(), pq.end(), min);
	for (auto i = 0; i < pq.size(); ++i) 
		map[pq[i]] = i;
	
	// push_heap
	input.push_back(4);
	pq.push_back(input.size()-1);
	map.push_back(input.size()-1);
	std::push_heap(pq.begin(), pq.end(), min);

	// decrease_key
	input[2] = 11;
	std::push_heap(pq.begin(), pq.begin() + map[2] + 1, min);

	// pop_heap
	while (pq.size() > 0) {
		std::pop_heap(pq.begin(), pq.end(), min);
		std::cout << pq.back() << "->" << input[pq.back()] << "\n";
		map[pq.back()] = -1;
		pq.pop_back();
	}

	return 0;
}
