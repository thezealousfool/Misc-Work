/*input
1
8
1 3 7 6 5 8 2 4
*/
#include <iostream>
#include <vector>
#include <cmath>

void find_swap (std::vector<int>& v, int i) {
	int min = v[i];
	int pos_min = i;
	if (v[i+1] < min) {
		min = v[i+1];
		pos_min = i+1;
	}
	if (v[i+2] < min) {
		min = v[i+2];
		pos_min = i+2;
	}
	int v_i = v[i];
	int v_i1 = v[i+1];
	int v_i2 = v[i+2];
	if (pos_min == i)
		return;
	if (pos_min == i+1) {
		v[i] = v_i1;
		v[i+1] = v_i2;
		v[i+2] = v_i;
		return;
	}
	v[i] = v_i2;
	v[i+1] = v_i;
	v[i+2] = v_i1;
}

int main() {
	int T;
	std::cin>>T;
	while (T--) {
		int N;
		std::cin>>N;
		std::vector<int> v(N);
		for (int i=0; i<N; ++i)
			std::cin>>v[i];
		for (int i=0; i<N; ++i) {
			for (int j=0; j<N-2; ++j)
				find_swap(v, j);
		}
		int i;
		for (i=0; i<N; ++i) {
			if (v[i]!=i+1) {
				std::cout<<"NO"<<std::endl;
				break;
			}
		}
		if (i==N)
			std::cout<<"YES"<<std::endl;
	}
	return 0;
}