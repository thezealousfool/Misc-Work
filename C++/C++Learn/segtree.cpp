#include <iostream>
#include <vector>
#include <cmath>
#include <limits>

void populate_segtree(std::vector<int>& input, std::vector<int>& tree, std::vector<int>& start, std::vector<int>& end, int index) {
	if (((index << 1) + 1) < tree.size()) {
		start[(index << 1) + 1] = start[index];
		end[(index << 1) + 2] = end[index];
		end[(index << 1) + 1] = ((end[index] - start[index]) >> 1) + start[index];
		start[(index << 1) + 2] = end[(index << 1) + 1] + 1;
		if (start[(index << 1) + 2] > end[(index << 1) + 2])
			start[(index << 1) + 2] = end[(index << 1) + 2];  
		populate_segtree(input, tree, start, end, (index << 1) + 1);
		populate_segtree(input, tree, start, end, (index << 1) + 2);
		tree[index] = tree[(index << 1) + 1] < tree[(index << 1) + 2] ? tree[(index << 1) + 1] : tree[(index << 1) + 2];
	}
	else {
		tree[index] = input[start[index]];
	}
}	
int query_tree (std::vector<int>& tree, std::vector<int>& start, std::vector<int>& end, int index1, int index2, int present) {
	if (index1 <= start[present] && index2 >= end[present]) {
			return tree[present];
	}
	if (index1 > end[present] || index2 < start[present]) {
		return std::numeric_limits<int>::max();
	}
	int temp1 = query_tree(tree, start, end, index1, index2, (present << 1) + 1);
	int temp2 = query_tree(tree, start, end, index1, index2, (present << 1) + 2);
	std::cout << "temp1 : " << temp1 << " temp2 : " << temp2 << "\n";
	return temp1 < temp2 ? temp1 : temp2;
}
int main() {
	int N = 6;
	int array_max = pow(2, ceil(log2(N)) + 1) - 1;
	std::vector<int> input = {2,8,3,7,1,4};
	std::vector<int> tree(array_max);
	std::vector<int> start(array_max);
	std::vector<int> end(array_max);
	start[0] = 0; end[0] = N-1;
	populate_segtree(input, tree, start, end, 0);
	std::cout << query_tree(tree, start, end, 1, 4, 0) << "\n";
}
