/*input
4
1 1 1 1
0 1 0 1
0 1 1 0
1 0 1 1
*/
#include <iostream>
#include <vector>

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

bool solve_maze(vector2D<int>& maze, vector2D<int>& solution, int x, int y, int N) {
	if (x == y && x == N-1)
		return true;

	auto validate_move = [&maze, &solution, &N] (int x, int y) {
		return (x < N && y < N && x >= 0 && y >= 0 && maze(x, y)==1);
	};

	for (int i=0; i<2; ++i) {
		x += i; y+= 1-i;
		if (validate_move(x, y)) {
			solution(x, y) = 1;
			if (solve_maze(maze, solution, x, y, N))
				return true;
			solution(x, y) = 0;
		}
		x -= i; y-= 1-i;
	}
	return false;
}

int main() {
	int N;

	std::cin >> N;

	vector2D<int> maze(N, N);
	vector2D<int> solution(N, N);

	for (int i=0; i<N; ++i) {
		for (int j=0; j<N; ++j)
			std::cin >> maze(i, j);
	}

	solution.fill(0);
	solution(0, 0) = 1;

	if (solve_maze(maze, solution, 0, 0, N)) {
		for (int i=0; i<N; ++i) {
			for (int j=0; j<N; ++j)
				std::cout << solution(i, j) << " ";
			std::cout << std::endl;
		}
	}
	else
		std::cout << "No solution exists!!" << std::endl;

	return 0;
}