#include <iostream>
#include <iomanip>
using std::cin; using std::cout;

int main() {
	int T;
	long long int s, v;
	long double res;
	cin >> T;
	while(T--) {
		cin >> s >> v;
		res = (long double)(2*s)/(3*v);
		cout << std::fixed << std::setprecision(7);
		cout << res << "\n";
	}
	return 0;
}
