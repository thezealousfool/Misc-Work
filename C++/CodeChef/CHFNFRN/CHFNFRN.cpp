#include <iostream>
#include <vector>
#include <algorithm>

bool check_entry (int j, std::vector<int>& table, std::vector<std::vector<bool>>& adj_mat) {
	for (int i = 0; i < table.size(); ++i) {
		if (!adj_mat[table[i]][j]) {
			return false;
		}
	}
	return true;
}

bool compute (std::vector<int>& table1, std::vector<int>& table2, std::vector<int>& table3, std::vector<std::vector<bool>> adj_mat) {
	for (int j = 0; j < table3.size(); ++j) {
		if (table1.size() == 0) {
			table1.push_back(j);
			continue;
		}
		bool check1 = check_entry(table3[j], table1, adj_mat);
		bool check2 = check_entry(table3[j], table2, adj_mat);
		if (check1 && check2) {
		}
		else if (check1) {
			table1.push_back(j);
			
		}
		else if (check2) {
			// std::cout << "Adding " << j+1 << " to table 2\n";
			table2.push_back(j);
		}
		else {
			// std::cout << j+1 << " cannot find place in any table\n";
			flag = true;
			break;
		}
	}
}

int main() {
	int T, N, M, src, dst;
	bool flag = true;
	std::cin >> T;
	std::vector<int> table1, table2, table3;
	// std::vector<bool> frnds;
	table1.reserve(1001);
	table2.reserve(1001);
	table3.reserve(1001);
	while (T--) {
		std::cin >> N >> M;
		// frnds.resize(N);
		std::vector<std::vector<bool>> adj_mat(N, std::vector<bool>(N, false));
		for (int i = 0; i < M; ++i) {
			std::cin >> src >> dst;
			adj_mat[src-1][dst-1] = true;
			adj_mat[dst-1][src-1] = true;
		}
		for (int i = 0; i < N; ++i)
			adj_mat[i][i] = true;
		if (N < 3) {
			std::cout << "YES\n";
			continue;
		}
		flag = false;
		table1.resize(0);
		table2.resize(0);
		table3.resize(0);
		// for (int sz = 0; sz < frnds.size(); ++sz)
		// 	frnds[sz] = false;
		

		if (flag) {
			std::cout << "NO\n";
			continue;
		}

		while (table3.size() > 0) {
			int initial_size = table3.size();
			for (int ii = 0; ii < table3.size(); ++ii) {
				bool check1 = check_entry(table3[ii], table1, adj_mat);
				bool check2 = check_entry(table3[ii], table2, adj_mat);
				if (check1 && check2) {}
				else if (check1) {
					table1.push_back(table3[ii]);
					table3[ii] = table3.back();
					table3.pop_back();
					--ii;
				}
				else if (check2) {
					table1.push_back(table3[ii]);
					table3[ii] = table3.back();
					table3.pop_back();
					--ii;
				}
				else {
					flag = true;
					break;
				}
			}
			if (flag)
				break;
			if (table3.size() == initial_size)
				break;
		}

		// std::cout << "\n\nTable1: \n";
		// for (const auto& ll : table1)
		// 	std::cout << ll+1 << " , ";
		// std::cout << "\n\nTable2: \n";
		// for (const auto& ll : table2)
		// 	std::cout << ll+1 << " , ";
		// std::cout << "\n";
		if (flag) {
			std::cout << "NO\n";
			continue;
		}
		
		if (table3.size() > 0) {
			for (int ii = 0; ii < table3.size(); ++ii) {
				if (check_entry(table3[ii], table3, adj_mat)) {
					table3[ii] = table3.back();
					table3.pop_back();
					--ii;
				}
			}
			if (table3.size() == 0) {
				std::cout << "YES\n";
				continue;
			}
			table1.resize(0);
			table2.resize(0);
			do {
				int initial_size = table3.size();
				for (int ii = 0; ii < table3.size(); ++ii) {
					if (table1.size() == 0) {
						table1.push_back(table3[ii]);
						table3[ii] = table3.back();
						table3.pop_back();
						--ii;
						continue;
					}
					bool check1 = check_entry(table3[ii], table1, adj_mat);
					bool check2 = check_entry(table3[ii], table2, adj_mat);
					if (check1 && check2) {}
					else if (check1) {
						table1.push_back(table3[ii]);
						table3[ii] = table3.back();
						table3.pop_back();
						--ii;
					}
					else if (check2) {
						table2.push_back(table3[ii]);
						table3[ii] = table3.back();
						table3.pop_back();
						--ii;
					}
					else {
						flag = true;
						break;
					}
				}
				if (flag) {
					std::cout << "NO\n";
					break;
				}
				if (table3.size() == 0) {
					std::cout << "YES\n";
				}
				if (table3.size() == initial_size) {
					table1.resize(0);
					table2.resize(0);
				}
			} while (table3.size() > 0);
		}
		else {
			std::cout << "YES\n";
		}
	}
	return 0;
}