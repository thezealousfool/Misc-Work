#include <iostream>

typedef long long int int64;
using std::cin; using std::cout;

int main() {
	int T;
	int64 n, m, c;
	cin >> T;
	while (T--) {
		cin >> n >> m >> c;
		int64 count = 0;
		int64 req_b;
		for (int64 i = 1; i <= n; ++i) {
			req_b = c/i;
			if (req_b*i == c && req_b <= m)
				++count;
		}
		cout << count << "\n";
	}
	return 0;
}
