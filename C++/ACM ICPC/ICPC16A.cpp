#include <iostream>

int main() {
	int T;
	std::cin >> T;
	int x1, y1, x2, y2;
	int diff;
	while(T--) {
		std::cin >> x1 >> y1 >> x2 >> y2;
		diff = x2 - x1;
		if(diff != 0) {
			if((y2-y1) != 0) {
				std::cout << "sad\n";
				continue;
			}
			if(diff > 0) {
				std::cout << "right\n";
				continue;
			}
			else {
				std::cout << "left\n";
				continue;
			}
		}
		else {
			diff = y2 - y1;
			if(diff > 0) {
				std::cout << "up\n";
				continue;
			}
			else {
				std::cout << "down\n";
				continue;
			}
		}
	}
	return 0;
}