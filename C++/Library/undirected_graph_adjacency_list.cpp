#include <iostream>
#include <vector>

struct edge {
	int vertex_1, vertex_2, weight;
};

void create_adjacency_list (std::vector<edge>& edges, int no_of_vertices) {

	std::vector<std::vector<std::pair <int, int>>> adjacency_list(no_of_vertices);

	for (const edge& e : edges) {
		adjacency_list[e.vertex_1].push_back(std::make_pair(e.vertex_2, e.weight));
		adjacency_list[e.vertex_2].push_back(std::make_pair(e.vertex_1, e.weight));
	}

	/* uncomment if needed to print and check generated adjacency list
	auto print_adjacency_list = [&adjacency_list] () {
		for(int i = 0; i < adjacency_list.size(); ++i) {
			std::cout << i << ": " << std::endl;
			for (auto elem : adjacency_list[i]) {
				std::cout << "v: " << elem.first << "\td: " << elem.second << std::endl;
			}
		}
		std::cout << std::endl;
	};

	print_adjacency_list(); */
}

int main() {
	std::vector<edge> edges = { {0,1,4} , {7,0,8} , {1,7,11} , {7,8,7} , {7,6,1} , {1,2,8} , {6,8,6} , {8,2,2} , {6,5,2} , {2,5,4} , {2,3,7} , {3,5,14} , {3,4,9} , {5,4,10} };
	create_adjacency_list (edges, 9);
	return 0;
}