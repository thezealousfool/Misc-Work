#include <iostream>
#include <cmath>

typedef long long int Int;

/*input
*/

#include <iostream>
#include <cstdlib>

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

template <typename T>
bool miller_test(T number, T base) {
    T random = (rand() % (number-4)) + 2;
    T miller_value = modular_exponentiation<T> (random, base, number);
    if (miller_value == 1 || miller_value == number-1)
        return true;

    while(base != number-1) {
        miller_value = (miller_value * miller_value) % number;
        base *= 2;
        if (miller_value == 1)
            return false;
        if (miller_value == number-1)
            return true;
    }
    return false;
}

template <typename T>
bool is_prime (T number, T k_iterations = 4) {
    if (number <= 1 || number == 4)
        return false;
    if (number <= 3)
        return true;
    T base = number - 1;
    while (base%2 == 0) {
        base /= 2;
    }
    while(k_iterations--) {
        if (!miller_test<T>(number,base))
            return false;
    }
    return true;
}

int main() {
    Int n;
    std::cin >> n;
    Int limit = (Int)pow(n, 0.25);
    Int count = 0;
    for (Int i = 0; i < limit; ++i) {
        if(is_prime<Int>(i))
    }
}