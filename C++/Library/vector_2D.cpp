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

int main() {
	vector2D<int> v(2, 3, {2,2,2,2,2,2});
	// v.fill(2);
	// v(2, 3) = 5;
	for (int i=0; i<2; ++i) {
		for(int j = 0; j < 3; ++j) {
			std::cout<<v(i, j)<<" ";
		}
		std::cout<<std::endl;
	}
	return 0;
}