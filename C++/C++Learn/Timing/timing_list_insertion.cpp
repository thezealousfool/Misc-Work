#include <iostream>
#include <list>
#include <fstream>
#include <chrono>
#include <algorithm>

int main() {
    std::chrono::steady_clock::time_point start, end;
    std::size_t time;
    auto cin = std::fstream("input.txt", std::ios::in);
    int N;
    cin >> N;
    for (int n = 1; n < N; n += 100) {
        start = std::chrono::steady_clock::now();
        std::list<int> v;
        {
            int temp, i, j; std::list<int>::iterator k;
            for (i = 0; i < n; ++i) {
                cin >> temp;
                k = v.begin();
                for (j = 0; j < i; ++j, ++k) {
                    if (*k > temp) {
                        break;
                    }
                }
                v.insert(k, temp);
            }
        }
        end = std::chrono::steady_clock::now();
        time = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
        std::cout << n << "\t" << time << "\n";
    }
    return 0;
}