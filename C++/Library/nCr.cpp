#include <iostream>


template <typename T>
T C(T n, T r) {
	if (r>n/2) r = n-r;
	T ans = 1;
	for (T i =1; i<=r; ++i) {
		ans *= n-r+i;
		ans /= i;
	}
	return ans;
}



const int max = 100;
int pascal_triangle[max][max];
template <typename T>
void populate_triangle() {
	pascal_triangle[0][0] = 1;
	for (T i=0; i<=max; ++i) {
		pascal_triangle[i][0] = pascal_triangle[i][i] = 1;
	}
	for (T i=0; i<=max; ++i) {
		for (T j=1; j<i; ++j)
			pascal_triangle[i][j] = pascal_triangle[i-1][j] + pascal_triangle[i-1][j-1];
	}
}

int main() {
	populate_triangle<int> ();
	std::cout<<pascal_triangle[99][2]<<std::endl;

	std::cout<<C<int>(99,2)<<std::endl;
	return 0;
}