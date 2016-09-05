/*input
5
12 1
13 1
13 2
13 3
13 4
*/
#include <iostream>
#include <vector>

using uint64 = long long int;
const uint64 Mod = (uint64)1E9 + 7;

std::vector<uint64> chefonacci = {1, 2, 3, 5, 8, 13, 21, 34, 55, 89, 144, 233, 377, 610, 987, 1597, 2584, 4181, 6765, 10946, 17711, 28657, 46368, 75025, 121393, 196418, 317811, 514229, 832040, 1346269, 2178309, 3524578, 5702887, 9227465, 14930352, 24157817, 39088169, 63245986, 102334155, 165580141, 267914296, 433494437, 701408733};

uint64 no_of_chefonacci (uint64 X, int K, int N) {
	if (X == 0 && K == 0)
		return 1;

	if (X <= 0 || K <= 0 || N < 0) 
		return 0;

	if (chefonacci[N]*K < X)
		return 0;

	return (no_of_chefonacci(X, K, N-1) + no_of_chefonacci(X - chefonacci[N], K - 1, N)) % Mod;
}

int main() {
	int Q, K;
	uint64 X;
	std::cin >> Q;
	while (Q--) {
		std::cin >> X >> K;
		std::cout << no_of_chefonacci(X, K, chefonacci.size()) << "\n";
	}
	return 0;
}