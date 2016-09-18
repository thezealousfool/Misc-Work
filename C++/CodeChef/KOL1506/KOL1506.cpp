/*input
5
2 2
7 2
2 3
7 2
3 2
1 3 2
10 2
1 2 3 4 5 6 7 8 9 10
10 10
1 2 3 4 5 6 7 8 9 10
*/

// Samosa Bhai and his Courier Company

#include <iostream>
#include <vector>

inline int exp (int base, int exponent, int mod) {
    if (base >= mod) {
        base = base % mod;
    }
    long long int result = 1;
    while (exponent > 0) {
        if (exponent & 1) {
            result = (result*base) % mod;
        }
        exponent /= 2;
        base = (base * base) % mod;
    }
    return (int)result;
}

inline int charge (int distance, int k) {
    return exp (distance, k, 1000000007);
}
int main() {
    int T;
    int N, k, amt;
    std::cin >> T;
    std::vector<int> plot;
    plot.reserve((int)1E5);
    while (T--) {
        std::cin >> N >> k;
        plot.resize(N);
        for (int i = 0; i < N; ++i) {
            std::cin >> plot[i];
        }
        amt = 0;
        for (int i = N-1; i > 0; --i) {
            for (int j = i-1; j >= 0; --j) {
                amt = (amt + charge(std::abs(plot[i] - plot[j]), k)) % 1000000007;
            }
        }
        std::cout << (2*amt) % 1000000007 << "\n";
    }
    return 0;
}