#include <iostream>
#include <vector>
#include <algorithm>

typedef long long int Int;

int main() {
    Int T;
    std::cin >> T;
    while(T--) {
        Int N;
        std::cin >> N;
        std::vector<Int> inp(N);
        std::vector<Int> dp(N, 1);
        for (Int k = 0; k < N; ++k) {
            std::cin >> inp[k];
        }
        std::sort(inp.begin(), inp.end());
        for (Int k = 1; k < N; ++k) {
            if (inp[k] - inp[k-1] < 2)
                dp[k] = dp[k-1] + inp[k] - inp[k-1];
        }
        Int max = 1;
        for (Int k = 1; k < N; ++k) {
            if (dp[k] > max)
                max = dp[k];
        }
        std::cout << max << '\n';
    }
    return 0;
}
