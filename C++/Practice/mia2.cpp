#include <iostream>
#include <vector>
#include <algorithm>

typedef long long int Int;

int main() {
    Int T;
    std::cin >> T;
    while(T--) {
        std::vector<bool> hash(1E5, false);
        std::vector<Int> dp(1E5, 0);
        Int N;
        std::cin >> N;
        for (Int k = 0; k < N; ++k) {
            Int loc;
            std::cin >> loc;
            hash[loc] = true;
        }
        if (hash[0]) {
            dp[0] = 1;
        }
        for (Int k = 1; k < 1E5; ++k) {
            if (hash[k])
                dp[k] = dp[k-1] + 1;
        }
        Int max = 1;
        for (Int k = 1; k < 1E5; ++k) {
            if (dp[k] > max)
                max = dp[k];
        }
        std::cout << max << '\n';
    }
    return 0;
}
