#include <iostream>
#include <array>

constexpr int n = 4, m = 4;

double solve(std::array<std::array<double, m>, n>& board, int length_x, int length_y) {
	if (length_x == 1 && length_y == 1)
		return board[0][0];
	double max = 0.0;
	double temp = 0.0;
	std::array<std::array<double, m>, n> temp_board;
	for (int i = 0; i < length_x; ++i) {
		for (int j = 1; j < length_y; ++j) {
			for (int k = 0; k < length_x; ++k) {
				if (k > i) {
					temp_board[j-1][k-1] = board[j][k];
				}
				else if (k < i) {
					temp_board[j-1][k] = board[j][k];
				}
			}
		}
		temp = board[0][i] + solve(temp_board, length_x - 1, length_y - 1);
		max = std::max(max, temp);
	}
	for (int i = 0; i < length_y; ++i) {
		for (int j = 0; j < length_y; ++j) {
			for (int k = 1; k < length_x; ++k) {
				if (j > i) {
					temp_board[j-1][k-1] = board[j][k];
				}
				else if (j < i) {
					temp_board[j][k-1] = board[j][k];
				}
			}
		}
		temp = board[i][0] + solve(temp_board, length_x - 1, length_y - 1);
		max = std::max(max, temp);
	}
	return max;
}

int main() {
	std::array<std::array<double, m>, n> board;
	for (int i = 0; i < n; ++i) {
		for (int j = 0; j < m; ++j) {
			std::cin >> board[i][j];
		}
	}
	getchar();
	std::cout << "max_sum: " << solve(board, m, n) << "\n";
	return 0;
}