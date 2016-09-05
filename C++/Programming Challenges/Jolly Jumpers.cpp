#include <iostream>
#include <vector>

int main() {
    std::ios::sync_with_stdio(false);
    int n;
    while (std::cin >> n) {
        bool flag = false;
        std::vector<int> v(n);
        std::vector<bool> check(n-1, false);
        for (int i=0; i<n; ++i) {
            std::cin >> v[i];
        }
        for (int i=1; i<n; ++i) {
            check[std::abs(v[i] - v[i-1]) - 1] = true;
        }
        for (const auto& elem : check) {
            if (elem == false) {
                std::cout << "Not Jolly\n";
                flag = true;
                break;
            }
        }
        if(!flag)
            std::cout << "Jolly\n";
    }
    return 0;
}