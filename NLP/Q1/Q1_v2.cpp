#include <iostream>
#include <vector>
#include <tuple>

int width = 0, height = 0;

struct elements {
	double value;
	int x, y;
	int accessible;
};

void mark_state(std::vector<elements>& board, int x, int y, int state) {
	for (int i = 0; i < width; ++i) {
		board[y*width + i].accessible += state;
	}

	for (int i = 0; i < height; ++i) {
		board[i*width + x].accessible += state;
	}
	board[y*width + x].accessible -= state;
}

double solve(std::vector<elements>& board) {
	int index = 0;
	while ((index < board.size()) && (board[index].accessible > 0)) {
		++index;
	}

	if (index == board.size()) {
		return 0.0;
	}

	int x = index % width, y = index / width;
	double max = 0.0, temp = 0.0;

	for (int i = x; i < width; ++i) {
		if (board[y*width + i].accessible > 0)
			continue;

		mark_state(board, i, y, 1);

		temp = board[y*width + i].value + solve(board);

		if (temp > max) {
			max = temp;
		}

		mark_state(board, i, y, -1);
	}

	// std::cout << "line 59 :  x: " << x << " y: " << y << "\n\n";
	for (int i = y; i < height; ++i) {
		if (board[i*width + x].accessible > 0)
			continue;

		mark_state(board, x, i, 1);

		temp = board[i*width + x].value + solve(board);

		if (temp > max) {
			max = temp;
		}

		mark_state(board, x, i, -1);
	}	

	return max;
}

int main() {
	int n, m;

	std::cout << "n: ";
	std::cin >> n;
	std::cout << "m: ";
	std::cin >> m;
	width = m;
	height = n;

	std::vector<elements> board(n*m);

	{
		int index = 0;
		for (auto& elem : board) {
			std::cin >> elem.value;
			elem.x = index % width; elem.y = index / width;
			index++;
			elem.accessible = 0;
		}
	}

	std::cout << "Maximum sum: " << solve(board) << "\n";
	
	return 0;
}