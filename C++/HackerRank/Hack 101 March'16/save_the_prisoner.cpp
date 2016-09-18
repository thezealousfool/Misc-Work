/*input
2
5 9 3
5 2 1
*/
#include <iostream>

typedef long long int Int;

int main() {
	int T;
	std::cin>>T;
	while (T--) {
		Int N, M, S;
		std::cin>>N>>M>>S;
		--S;
		S = (S+M) % N;
		std::cout<<S<<std::endl;
	}
	return 0;
}