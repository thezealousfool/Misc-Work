#include <iostream>

int main() {
	std::ios::sync_with_stdio(false);
	long long int T, n, inp;
	int count_1, count_m1, count_g1;
	bool printed;
	std::cin >> T;
	while (T--) {
		printed = false;
		count_1 = count_m1 = count_g1 = 0;
		std::cin >> n;
		if(n == 1) {
			std::cin >> inp;
			std::cout << "yes\n";
			continue;
		}
		while(n--) {
			std::cin >> inp;
			if(inp == 0 || printed)
				continue;
			if(inp > 1 || inp < -1) {
				if(count_g1 > 0 || count_m1 > 0) {
					std::cout << "no\n";
					printed = true;
				}
				else {
					++count_g1;
				}
			}
			else if(inp == -1) {
				if(count_g1 > 0) {
					std::cout << "no\n";
					printed = true;
					continue;
				}
				if(count_m1 < 2)
					++count_m1;
			}
			else {
				if(count_1 == 0)
					count_1 = 1;
			}	
		}
		if(!printed) {
			if(count_m1 > 1) {
				if(count_1 > 0)
					std::cout << "yes\n";
				else
					std::cout << "no\n";
			}
			else {
				std::cout << "yes\n";
			}
		}
	}
	return 0;
}