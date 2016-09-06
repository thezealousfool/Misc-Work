#include <iostream>
#include <vector>
#include <algorithm>

bool check_entry (int j, std::vector<int>& table, std::vector<std::vector<int>>& adj_list) {
	for (const auto& i : table) {
		if (std::find(adj_list[j].begin(), adj_list[j].end(), i) == adj_list[j].end()) {
			return false;
		}
	}
	return true;
}

int main() {
	int T, N, M, src, dst;
	bool flag = true;
	std::cin >> T;
	std::vector<bool> frnds;
	std::vector<int> table1, table2;
	table1.reserve(1001);
	table2.reserve(1001);
	frnds.reserve(1001);
	while (T--) {
		std::cin >> N >> M;
		frnds.resize(N);
		std::vector<std::vector<int>> adj_list(N);
		for (int i = 0; i < M; ++i) {
			std::cin >> src >> dst;
			adj_list[src - 1].push_back(dst - 1);
			adj_list[dst - 1].push_back(src - 1);
		}
		for (int i = adj_list[0].size() - 1; i >= 0; --i) {
			flag = false;
			table1.resize(0);
			table2.resize(0);
			for (int sz = 0; sz < frnds.size(); ++sz)
				frnds[sz] = false;
			std::cout << "Adding 0 and " << adj_list[0][i] << " to table 1\n";
			table1.push_back(0);
			table1.push_back(adj_list[0][i]);
			frnds[0] = true;
			frnds[adj_list[0][i]] = true;
			for (int j = 0; j < N; ++j) {
				if (frnds[j])
					continue;
				if (check_entry(j, table1, adj_list)) {
					std::cout << "Adding " << j << " to table 1\n";
					table1.push_back(j);
					frnds[j] = true;
				}
				else {
					if (check_entry(j, table2, adj_list)) {
						std::cout << "Adding " << j << " to table 2\n";
						table2.push_back(j);
						frnds[j] = true;
					}
					else {
						std::cout << j << " cannot find place in any table\n";
						flag = true;
						break;
					}
				}
			}
			if (!flag)
				break;
		}
		if (flag) {
			std::cout << "NO\n";
		}
		else {
			std::cout << "YES\n";
		}
	}
	return 0;
}
