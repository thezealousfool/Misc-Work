// Has a problem of detecting a loop in line no 26 to 30

#include <iostream>
#include <vector>
#include <algorithm>
#include <functional>

struct edge {

	int source, destination, distance;
	bool visited;
};

int kuskal_MST (std::vector<edge>& edges, std::vector<int> vertices) {

	std::sort (edges.begin(), edges.end(), [] (const edge& e1, const edge& e2) {

		return e2.distance > e1.distance;
	});

	std::function<int (int)> add_edge = [&edges, &vertices, &add_edge] (int N) {

		if (N >= edges.size())
			return 0;
		edge& temp = edges[N];
		if ((vertices[temp.source] >1 && vertices[temp.destination] >= 1) || (vertices[temp.source] >=1 && vertices[temp.destination] > 1)) {
			std::cout << temp.source << "-----" << temp.destination << " = " << temp.distance << "    ";
			std::cout << "source: " << vertices[temp.source] << "   destination: " << vertices[temp.destination] << std::endl;
			return add_edge(N+1);
		}
		std::cout << temp.source << "-----" << temp.destination << " = " << temp.distance << std::endl;
		++vertices[temp.source];
		++vertices[temp.destination];
		return temp.distance + add_edge(N+1);
	};

	return add_edge(0);
}

int main() {

	std::vector<edge> edges = { {0,1,4} , {7,0,8} , {1,7,11} , {7,8,7} , {7,6,1} , {1,2,8} , {6,8,6} , {8,2,2} , {6,5,2} , {2,5,4} , {2,3,7} , {3,5,14} , {3,4,9} , {5,4,10} };
	std::vector<int> vertices(9);
	std::fill(vertices.begin(), vertices.end(), 0);
	int total_distance = kuskal_MST (edges, vertices);
	std::cout << "The total distance to be travelled: " << total_distance << std::endl;
	return 0;
}