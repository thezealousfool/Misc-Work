#include <iostream>
#include <vector>
#include <cmath>

std::vector<int> operator+(std::vector<int>& v1, std::vector<int>& v2) {
	std::vector<int> v(v1.size() + v2.size());
	int index1 = 0, index2 = 0, index = 0;
	while(index1 < v1.size() && index2 < v2.size()) {
		if (index1 == v1.size()) {
			while (index2 < v2.size()) {
				v[index++] = v2[index2++];
			}
		}
		else if (index2 == v2.size()) {
			while (index1 < v1.size()) {
				v[index++] = v1[index1++];
			}
		}
		else {
			if (v1[index1] < v2[index2]) {
				v[index++] = v1[index1++];
			}
			else {
				v[index++] = v2[index2++];
			}
		}
	}
	return v;
}

void create_segtree(std::vector<int>& array, std::vector<int> segtree, std::vector<int> start, std::vector<int> end, int index) {
}

void populate_start_end(std::vector<int>& start, std::vector<int>& end, int no_of_elements) {
	int index = start.size() / 2;
	int value = 0;

	while(index < start.size()) {
		start[index] = end[index] = value;
		++index; ++value;
	}

	int negative = 0;
	value = ((start.size() + 1) / 2) - no_of_elements;
	index = start.size() - (2 * negative + 1) - 4 * (value - 1);

	while(value > 0) {
		start[index] = end[index] = start[index - 1];
		++index;
		start[index] = end[index] = start[index - 1] + 1;
		++index;
		--value;
	}

	index = start.size() / 2 - 1;

	while(index >= 0) {
		start[index] = start[2*index + 1];
		end[index] = end[2*index + 2];
		--index;
	}
}

int main() {
	int n, m;

	std::vector<int> array;
	std::vector<int> segtree;
	std::vector<int> start;
	std::vector<int> end;
	
	std::cin >> n >> m;
	
	array.resize(n);
	segtree.resize((int)pow(2,ceil(log2(n)) + 1) - 1);
	start.resize(segtree.size());
	end.resize(segtree.size());
	
	// for(auto& elem : array) {
		// std::cin >> elem;
	// }
	
	start[0] = 0;
	end[0] = n-1;

	populate_start_end(start, end, n);
	//create_segtree(array, segtree, start, end, 0);
	
	for(int i = 0; i < segtree.size(); ++i) {
		std::cout << "(" << start[i] << "," << end[i] << ")\n";
	}

	return 0;
}