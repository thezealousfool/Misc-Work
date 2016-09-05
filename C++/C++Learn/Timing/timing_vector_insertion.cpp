#include <iostream>
#include <vector>
#include <chrono>
#include <fstream>

int main() {
    std::chrono::steady_clock::time_point start, end;
    std::size_t time;
    auto cin = std::fstream("input.txt", std::ios::in);
    int N;
    cin >> N;
    for (int n = 1; n <= N; n += 100) {
        start = std::chrono::steady_clock::now();
        std::vector<int> v(n);
        for (int i = 0, temp, j, k; i < n; ++i) {
            cin >> temp;
            for (j = 0; j < i; ++j) {
                if (v[j] > temp) {
                    for (k = i-1; k >= j; --k) {
                        v[k+1] = v[k];
                    }
                    break;
                }
            }
            v[j] = temp;
        }
        end = std::chrono::steady_clock::now();
        time = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
        std::cout << n << "\t" << time << "\n";
    }
    return 0;
}