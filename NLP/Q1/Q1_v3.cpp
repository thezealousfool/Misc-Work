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

std::tuple<double, std::vector<elements>> solve(std::vector<elements>& board) {
	int index = 0;
	while ((index < board.size()) && (board[index].accessible > 0)) {
		++index;
	}

	if (index == board.size()) {
		return std::make_tuple(0.0, std::vector<elements>());
	}

	int x = index % width, y = index / width;
	double max = 0.0;
	std::vector<elements> path;
	path.reserve(std::min(width-x,height-y) + 2);

	for (int i = x; i < width; ++i) {
		if (board[y*width + i].accessible > 0)
			continue;

		mark_state(board, i, y, 1);

		auto temp = solve(board);

		if (std::get<0>(temp) + board[y*width + i].value > max) {
			max = std::get<0>(temp) + board[y*width + i].value;
			while(path.size()) {
				path.pop_back();
			}
			path.push_back(board[y*width + i]);
			for (const auto& e : std::get<1>(temp)) {
				path.push_back(e);
			}
		}

		mark_state(board, i, y, -1);
	}

	for (int i = y; i < height; ++i) {
		if (board[i*width + x].accessible > 0)
			continue;

		mark_state(board, x, i, 1);

		auto temp = solve(board);

		if (std::get<0>(temp) + board[i*width + x].value > max) {
			max = std::get<0>(temp) + board[i*width + x].value;
			while(path.size()) {
				path.pop_back();
			}
			path.push_back(board[i*width + x]);
			for (const auto& e : std::get<1>(temp)) {
				path.push_back(e);
			}
		}

		mark_state(board, x, i, -1);
	}	

	return std::make_tuple(max, path);
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

	auto return_value = solve(board);

	std::cout << "\nMaximum sum: " << std::get<0>(return_value) << "\n\n";

	std::cout << "Path: \n";
	for (const auto& elem : std::get<1>(return_value))
		std::cout << "(" << elem.x << ", " << elem.y << ")   :   " << elem.value << "\n";
	
	return 0;
}