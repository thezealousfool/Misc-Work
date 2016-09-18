#include <iostream>
#include <array>

using uint64 = unsigned long long int;

constexpr uint64 array_max = 8*(uint64)1e2 + 90;
constexpr uint64 Mod = (uint64)1e9 + 7;

std::array <uint64, array_max> fib_series;

template <uint64 index>
void populate() {
    populate<index - 1> ();
    fib_series[index]  = (fib_series[index - 1] + fib_series[index - 2]) % Mod;
}

template <>
void populate<1>() {
}

int main() {
    fib_series[0] = 0; fib_series[1] = 1;
    populate<array_max - 1>();
    for (int i = 0; i < array_max; ++i)
        std::cout << fib_series[i] << "\n";
    return 0;
}