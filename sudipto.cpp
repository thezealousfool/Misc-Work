#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

int check_next (const std::string& st1, const std::string& st2, int st1_index, int st2_index) {
	if (st1[st1_index] < st2[st2_index]) {
		return 0;
	}
	else if (st1[st1_index] > st2[st2_index]) {
		return 1;
	}
	else {
		return 1+check_next(st1, st2, st1_index+1, st2_index+1);
	}
}

int main() {
	std::string st1, st2;
	int st1_index, st2_index;
	int T;
	std::cin >> T;
	std::vector<std::string> v(T);
	while(T--) {
		std::cin >> st1 >> st2;
		st1_index = st2_index = 0;
		std::string st3(st1.length()+st2.length(), ' ');
		for (int i = 0; i < st3.length(); ++i) {
			if (st2_index >= st2.length()) {
				st3[i] = st1[st1_index];
				++st1_index;
			}
			else if (st1_index >= st1.length()) {
				st3[i] = st2[st2_index];
				++st2_index;
			}
			else if (st1[st1_index] < st2[st2_index]) {
				st3[i] = st1[st1_index];
				++st1_index;
			}
			else if (st1[st1_index] == st2[st2_index]) {
				int code = check_next(st1, st2, st1_index+1, st2_index+1);
				if (code == 1) {
					st3[i] = st2[st2_index];
					++st2_index;
				}
				else {
					st3[i] = st1[st1_index];
					++st1_index;
				}
			}
			else {
				st3[i] = st2[st2_index];
				++st2_index;
			}
		}
		v[T] = st3;
	}
    std::for_each(v.crbegin(), v.crend(), [](std::string s) {std::cout << s << "\n";});
	return 0;
}