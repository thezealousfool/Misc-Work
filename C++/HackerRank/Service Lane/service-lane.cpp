/*input
8 5
2 3 1 2 3 2 3 3
0 3
4 6
6 7
3 5
0 7
*/
#include <iostream>
#include <vector>

typedef long long int Int;

int main() {
	Int N;
	std::cin>>N;
	std::vector<int> lane_width(N);
	int T;
	std::cin>>T;
	for (Int i=0; i<N; ++i)
		std::cin>>lane_width[i];
	while (T--) {
		Int i, j;
		std::cin>>i>>j;
		int min = 3;
		for (Int k=i; k<=j; ++k) {
			if (lane_width[k]<min)
				min = lane_width[k];
			if (min==1)
				break;
		}
		std::cout<<min<<std::endl;
	}
	return 0;
}