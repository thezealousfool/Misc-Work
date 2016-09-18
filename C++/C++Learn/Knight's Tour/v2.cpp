#include <iostream>
#include <vector>
#define N 8

template <typename container_type>
class vector2D {
private:
	int column;
	std::vector<container_type> v;

public:
	vector2D() {
		column = 0;
	}

	vector2D(int n, int m) {
		v.resize(n*m);
		column = m;
	}

	vector2D(int n, int m, std::initializer_list<container_type> args) {
		v.resize(n*m);
		int i = 0;
		for (container_type elem : args) {
			v[i] = elem;
			++i;
		}
		column = m;
	}

	void fill (container_type&& value) {
		std::fill (v.begin(), v.end(), value);
	}

	std::vector<container_type>& get_vector_reference() {
		return v;
	}

	int get_column() {
		return column;
	}

	container_type& operator= (const vector2D& v2) {
		(this)->v = v2.get_vector_reference();
		(this)->column = v2.get_column();
		return this;
	}

	void push_back(container_type& elem) {
		v.push_back(elem);
	}

	container_type& operator() (int i, int j) {
		return v[i*column + j];
	}
};

std::vector<std::pair<int, int>> moves(8);

bool solveKT (vector2D<int>& board, int x, int y, int move_no) {
	// board.print_board();
	if (move_no==N*N)
		return true;

	auto validate_move = [&board](int x, int y) {
		return (0<=x && x<N && 0<=y && y<N && board(x, y)==-1);
	};

	for(int i=0; i<8; ++i) {
		x += moves[i].first;
		y += moves[i].second;
		if (validate_move(x, y)) {
			++move_no;
			board(x, y) = move_no;
			if (solveKT(board, x, y, move_no))
				return true;
			board(x, y) = -1;
			-- move_no;
		}
		x -= moves[i].first;
		y -= moves[i].second;
	}
	return false;
}

int main() {
	vector2D<int> board(N, N);
	moves[0].first = 2;	moves[0].second = 1;
	moves[1].first = 1;	moves[1].second = 2;
	moves[2].first = -1;	moves[2].second = 2;
	moves[3].first = -2;	moves[3].second = 1;
	moves[4].first = -2;	moves[4].second = -1;
	moves[5].first = -1;	moves[5].second = -2;
	moves[6].first = 1;	moves[6].second = -2;
	moves[7].first = 2;	moves[7].second = -1;
	board.fill(-1);
	board(0, 0) = 1;
	// board.print_board();
	if (solveKT(board, 0, 0, 1)) {
		for (int i=0; i<N; ++i) {
			for (int j=0; j<N; ++j) {
				std::cout<<board(i,j)<<"\t";
			}
			std::cout<<std::endl;
		}
	}
	else {
		std::cout<<"No solution exists!!"<<std::endl;
	}
	return 0;
}