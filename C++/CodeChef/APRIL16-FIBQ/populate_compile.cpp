#include <iostream>
#include <array>

using uint64 = unsigned long long int;

constexpr uint64 array_size = (uint64)1e7 + 2;
constexpr uint64 Mod = (uint64)1e9 + 7;

std::array<uint64, array_size> fibonacci_series;

constexpr void populate_fib_series(uint64 index) {
    if (index == 2) {
        fibonacci_series[2] = 1;
        return;
    }
    if (index == 1) {
        fibonacci_series[1] = 1;
        return;
    }
    populate_fib_series(index - 1);
    fibonacci_series[index] = fibonacci_series[index - 1] + fibonacci_series[index - 2];
}

int main() {
    populate_fib_series(array_size - 1);
    // std::array<int, fibonacci_series[array_size - 1]> temp;
    // std::cout << temp.size() << "\n";
    return 0;
}