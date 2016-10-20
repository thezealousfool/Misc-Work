#include <iostream>

long long int count(std::string& s) {
	int len = s.length();
	long long int res = 0;
	for (int i = 0; i < len; ++i) {
		if(s[i] == '1') {
			++res;
		}
	}
	return res;
}
int main() {
	std::ios_base::sync_with_stdio(false);
	int T;
	long long int res, no;
	std::string head, body, foot;
	std::cin >> T;
	while(T--) {
		no = 0;
		res = 0;
		std::cin >> head >> body >> foot;
		std::cin >> no;
		if(foot[foot.length()-1] = 0) {
			res = 1;
			res += count(head);
			res += count(body)*no;
			res += count(foot);
		}
		else {
			res = count(foot);
			if(res == foot.length()) {
				
			}
		}
	}
}