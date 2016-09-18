#include <iostream>
#include <chrono>
#include <vector>
#include <cmath>

using uint64 = unsigned long long int;
const uint64 Mod = (uint64)1E9 + 7;

std::vector<uint64> fib_cache(Mod, -1);

uint64 fib (uint64 index) {
    std::cout << "fib " << index << "\n";
    if (index < 0) { 
        std::cout << "fib done \n";
        return 0;
    }
    if (fib_cache[index + 1] != -1) {
        std::cout << "fib done \n";
        return fib_cache[index + 1];
    }
    uint64 A = index / 2;
    uint64 B = index - index / 2;
    uint64 temp = ((fib(A) * fib(B + 1)) % Mod) + ((fib(A - 1) * fib(B)) % Mod);
    temp %= Mod;
    fib_cache[index + 1] = temp;
        std::cout << "fib done \n";
    return temp;
}

void populate_segtree (std::vector<uint64>& array, std::vector<uint64>& segtree_fib_minus_one, std::vector<uint64>& segtree_fib, std::vector<uint64>& segtree_fib_plus_one, std::vector<uint64>& start, std::vector<uint64>& end, uint64 index) {
    if (2*index + 1 > segtree_fib.size()) {
        segtree_fib_minus_one[index] = fib(array[start[index]] - 1);
        segtree_fib[index] = fib(array[start[index]]);
        segtree_fib_plus_one[index] = fib(array[start[index]] + 1);
        return;
    }
    start[2*index + 1] = start[index];
    end[2*index + 2] = end[index];
    end[2*index + 1] = start[index] + (end[index] - start[index]) / 2;
    start [2*index + 2] = std::min(end[2*index + 1] + 1, end[index]);
    populate_segtree(array, segtree_fib_minus_one, segtree_fib, segtree_fib_plus_one, start, end, 2*index + 1);
    populate_segtree(array, segtree_fib_minus_one, segtree_fib, segtree_fib_plus_one, start, end, 2*index + 2);
    segtree_fib[index] = (((segtree_fib[2*index + 1] * segtree_fib_plus_one[2*index + 2]) % Mod) + ((segtree_fib_minus_one[2*index + 1] * segtree_fib[2*index + 2]) % Mod)) % Mod;
    segtree_fib_minus_one[index] = (((segtree_fib[2*index + 1] * segtree_fib[2*index + 2]) % Mod) + ((segtree_fib_minus_one[2*index + 1] * segtree_fib_minus_one[2*index + 2]) % Mod)) % Mod;
    segtree_fib_plus_one[index] = (((segtree_fib_plus_one[2*index + 1] * segtree_fib_plus_one[2*index + 2]) % Mod) + ((segtree_fib[2*index + 1] * segtree_fib[2*index + 2]) % Mod)) % Mod;
}

int main() {
    auto time_start = std::chrono::steady_clock::now();
    std::ios::sync_with_stdio(false);
    fib_cache[0] = 0; fib_cache[1] = fib_cache[2] = 1; fib_cache[3] = 2; fib_cache[4] = 3;
    uint64 N, M;
    std::cin >> N >> M;
    std::vector<uint64> array(N);
    for (uint64 i = 0; i < N; ++i)
    {
        std::cin >> array[i];
    }
    std::vector<uint64> segtree_fib(std::pow(2, std::ceil(log2(N))) - 1);
    std::vector<uint64> segtree_fib_minus_one(segtree_fib.size());
    std::vector<uint64> segtree_fib_plus_one(segtree_fib.size());
    std::vector<uint64> start(segtree_fib.size());
    std::vector<uint64> end(segtree_fib.size());
    start[0] = 0; end[0] = N -1;
    populate_segtree(array, segtree_fib_minus_one, segtree_fib, segtree_fib_plus_one, start, end, 0);
    auto time = std::chrono::steady_clock::now() - time_start;
    std::cout << std::chrono::duration_cast<std::chrono::seconds>(time).count() << " seconds ";
    std::cout << std::chrono::duration_cast<std::chrono::milliseconds>(time).count() << " milliseconds ";
    std::cout << std::chrono::duration_cast<std::chrono::microseconds>(time).count() << " microseconds\n";
    return 0;
}