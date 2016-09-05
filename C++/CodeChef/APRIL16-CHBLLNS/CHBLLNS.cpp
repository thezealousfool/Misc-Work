/*input
1
1 1 5
3
*/
#include <iostream>

typedef long long int Int;

int main() {
    int T;
    Int R, G, B, K, result;
    std::cin >> T;
    while (T--) {
        std::cin >> R >> G >> B;
        std::cin >> K;
        result = 3*K - 2;
        if (R<K)
            result -= K-1-R;
        if (G<K)
            result -= K-1-G;
        if (B<K)
            result -= K-1-B;
        std::cout << result << std::endl;
    }
    return 0;
}