#include <iostream>

using Int = long long int;

Int maximise (Int n) {
	if (n <= 11)
		return n;
	return std::max(n, maximise(n/2)+maximise(n/3)+maximise(n/4));
}

int main() {
	Int n;
	while (scanf("%lld", &n)!=EOF) {
		std::cout << maximise(n) << "\n";
	}
	return 0;
}
