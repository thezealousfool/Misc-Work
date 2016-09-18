#include <iostream>
#include <algorithm>
#include <vector>
#include <chrono>
#include <fstream>

int main() {
    auto cin = std::fstream("input.txt", std::ios::in);
    // int N;
    // cin >> N;
    // for (int n = 1; n < 40100; n += 100) {
    {
        int n = 40100;
        auto start = std::chrono::steady_clock::now();
        std::vector<int> v(n);
        for (auto& e : v) {
            cin >> e;
        }
        std::sort(v.begin(), v.end());
        auto end = std::chrono::steady_clock::now();
        auto time = std::chrono::duration_cast<std::chrono::milliseconds>(end-start).count();
        std::cout << n << "\t" << time << "\n";
    }
    return 0;
}