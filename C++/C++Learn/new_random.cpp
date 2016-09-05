#include <iostream>
#include <random>
#include <chrono>
#include <fstream>

int main() {
    std::size_t n, mod, i;
    auto fout = std::fstream("random.txt", std::ios::out);
    std::cout << "N: ";
    std::cin >> n;
    std::cout << "Mod: ";
    std::cin >> mod;
    std::default_random_engine e(std::chrono::steady_clock::now().time_since_epoch().count());
    std::uniform_int_distribution<std::size_t> distribution(0, mod-1);
    for (i = 0; i < n; ++i) {
        fout << distribution(e) << "\n";
    }
    return 0;
}