/*input
0
*/

#include <iostream>
#include <deque>
typedef long long int Int;

Int nearest (Int& k) {
	std::deque<int> queue;
	int A = k;
	while(A>0) {
		queue.push_front(A%10);
		A /= 10;
	}
	for(int i = 0; i < queue.size()/2; ++i) {
		
	}
}

int main() {
	int T;
	std::cin>>T;
	while(T--) {
		Int k;
		std::cin>>k;
		std::cout<<nearest(k)<<std::endl;
	}
	return 0;
}