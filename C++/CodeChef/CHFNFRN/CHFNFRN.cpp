#include <iostream>
#include <vector>

int main() {
	int T, N, M, no_tables, src, dst;
	std::cin >> T;
	std::vector<char> frnds;
	frnds.reserve(1001);
	while (T--) {
		std::cin >> N >> M;
		frnds.resize(N);
		for (auto& e : frnds)
			e = false;
		no_tables = 0;
		std::vector<std::vector<int>> adj_list(N);
		for (int i = 0; i < M; ++i) {
			std::cin >> src >> dst;
			adj_list[src].push_back(dst);
			adj_list[dst].push_back(src);
		}
	}
	return 0;
}
