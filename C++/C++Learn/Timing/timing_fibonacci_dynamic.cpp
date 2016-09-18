/*input
1 50000
*/

// input : 15               time : 287 milliseconds
// input : 1500           time : 295 milliseconds
// input : 1500000     time : 280 milliseconds
// input : 1 1500000	gcc		time : 10329 milliseconds
// input : 1 1500000	clang	time : 10316 milliseconds

#include <iostream>
#include <array>
#include <chrono>

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
    Int n, m;
    std::cin >> n >> m;
    std::chrono::steady_clock::time_point start = std::chrono::steady_clock::now();
    for (Int i=n; i<=m; ++i)
        std::cout << Nth_fibonacci(i) << std::endl;
    std::chrono::steady_clock::duration time = std::chrono::steady_clock::now() - start;
    std::cout << "Time taken: " << std::chrono::duration_cast<std::chrono::milliseconds>(time).count() << " milliseconds" << std::endl;
    return 0;
}