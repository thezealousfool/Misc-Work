#include <iostream>
#include <algorithm>
#include <vector>
#include <map>
#include <string>

int main() {

	std::vector<std::string> input_keys = {"node1",
						"node2",
						"node3",
						"node4",
						"node5",
						"node6",
						"node7",
						"node8",
						"node9",
						"node10"};
	std::vector<double> input = {13.2,7.5,2.2,7.8,20.2,10.2,5.7,40.75,17.25,27.75};
	std::vector<int> pq(input.size());
	std::vector<int> map(input.size());
	for (auto i = 0; i < input.size(); ++i)
		pq[i] = i;


	// lambda
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


	// reduce_key
	input[7] = 25.75;
	std::push_heap(pq.begin(), pq.begin() + map[7] + 1, min);


	// pop_heap
	while (pq.size() > 0) {
		std::pop_heap(pq.begin(), pq.end(), min);
		std::cout << input_keys[pq.back()] << "\t->  " << input[pq.back()] << "\n";
	        map[pq.back()] = -1;
		pq.pop_back();	
	}

	return 0;
}
