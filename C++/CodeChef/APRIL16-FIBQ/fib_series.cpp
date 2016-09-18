#include <iostream>
#include <array>
#include <chrono>
#include <fstream>

using uint64 = unsigned long long int;

// constexpr uint64 array_size = static_cast<uint64>(1e6) + 2;
constexpr uint64 Mod = static_cast<uint64>(1e9) + 7;

int main() {
    uint64 a, b, c;
    // std::array<uint64, array_size> fib_series;
    auto fout = std::fstream("fib.txt", std::ios::out);
    auto start = std::chrono::steady_clock::now();
    // fib_series[0] = 0; fib_series[1] = 1;
    a = 0; b = 1;
    std::cout << "starting loop\n";
    for (uint64 i = 2; i < Mod - 7; ++i) {
        // fib_series[i] = (fib_series[i-1] + fib_series[i-2]) % Mod;
        c = (a + b) % Mod;
        // fout << fib_series[i] << "\n";
        std::cout << i << ", ";
        fout << c << ", ";
        a = b; b = c;
    }
    std::cout << "done\n";
    auto time = std::chrono::steady_clock::now() - start;
    std::cout << std::chrono::duration_cast<std::chrono::nanoseconds>(time).count() << " nanoseconds\n";
    return 0;
}