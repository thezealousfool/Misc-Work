/*input
1
2 1000000000
*/
#include <iostream>

typedef long long int Int;
const Int Mod = 1E9 + 7;

template <typename T>
T modular_exponentiation(T base, T power, T mod_base) {
    T result = 1;
    base = base % mod_base;

    while (power > 0) {
        if (power%2 == 1)
            result = (result * base) % mod_base;

        power /= 2;
        base = (base*base) % mod_base;
    }

    return result;
}

int main() {
    int T;
    Int N, K, result;
    std::cin >> T;
    while (T--) {
        std::cin >> N >> K;
        result = K;
        result = result * modular_exponentiation<Int> (K-1, N-1, Mod);
        result %= Mod;
        std::cout << result << std::endl;
    }
    return 0;
}