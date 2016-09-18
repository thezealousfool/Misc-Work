/*input
4
1 2 3 3
*/
#include <iostream>
#include <algorithm>

using uint64 = unsigned long long int;

int main() {
    std::ios::sync_with_stdio(false);
    uint64 n, temp;
    std::cin >> n;
    uint64 sum = 0, res;
    for (uint64 i = 1; i <= n; ++i) {
        std::cin >> temp;
        sum += temp;
    }
    res = std::max( (sum >> 1) + (sum & 1), n);
    std::cout << res << "\n";
    return 0;
}