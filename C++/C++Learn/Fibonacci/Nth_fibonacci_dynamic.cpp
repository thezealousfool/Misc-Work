/*input
15
*/
#include <iostream>
#include <array>

typedef long long int Int;
typedef long double Dob;

const Int Mod = 1E9 + 7;
const Int store_max = 1E8;

std::array<Int, store_max> fibonacci;
std::array<bool, store_max> calculated;

Int Nth_fibonacci (const Int& N) {
    if (N<=0) return 0;
    if (N < store_max && calculated[N-1]) return fibonacci[N-1];

    Int fib, number1, number2;
    number1 = N/2;
    number2 = N - number1;

    fib = (Nth_fibonacci(number2) * Nth_fibonacci(number1 + 1) + Nth_fibonacci(number2 - 1) * Nth_fibonacci(number1)) % Mod;

    if (N < store_max) {
        fibonacci[N-1] = fib;
        calculated[N-1] = true;
    }
    return fib;
}

int main() {
    fibonacci[0] = 1;
    fibonacci[1] = 1;
    calculated.fill(false);
    calculated[0] = true;
    calculated[1] = true;
    int n;
    std::cin >> n;
    std::cout << Nth_fibonacci(n) << std::endl;
    return 0;
}