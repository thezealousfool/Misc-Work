#include <iostream>
#include <vector>
#include <functional>
#define N 4

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

int main() {
	vector2D<int> board(N, N);
	vector2D<int> solution(N, N);
	board.fill(0);
	solution.fill(0);

	auto place_queen = [&board] (int x, int y, int value) {
		std::vector<std::pair<int, int>> v = { {0, -1}, {-1, 0}, {0, 1}, {1, 0}, {1, 1}, {1, -1}, {-1, 1}, {-1, -1} };
		for(auto p : v) {
			int x1 = x; int y1 = y;
			while (x1 < N && y1 < N && x1 >= 0 && y1 >= 0) {
				board(x1, y1) += value;
				x1 += p.first; y1 += p.second;
			}
		}
	};

	auto validity_check = [&board] (int x, int y) {
		return (x>=0 && y>=0 && x<N && y<N && board(x, y)==0);
	};

	std::function<bool (int)> solve_queen = [&] (int x) {
		if (x == N)
			return true;
		for(int y = 0; y < N; ++y) {
			if (validity_check(x, y)) {
				place_queen (x, y, 1);
				solution(x, y) = 1;
				if (solve_queen(x+1))
					return true;
				place_queen (x, y, -1);
				solution(x, y) = 0;
			}
		}
		return false;
	};

	if (solve_queen(0)) {
		for(int i = 0; i < N; ++i) {
			for(int j = 0; j < N; ++j) {
				std::cout<<solution(i, j)<<" ";
			}
			std::cout << std::endl;
		}
	}
	else 
		std::cout << "No solution exists!!" << std::endl;
	
	return 0;
}