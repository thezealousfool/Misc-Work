/*input
4
1
100
2
42 0
3
1 4 9
4
5 5 5 5
*/
#include <iostream>
#include <vector>
#include <cmath>
#include <array>

using uint64 = unsigned long long int;
std::array<std::array<unsigned int, 2000>, 2000> cache;

void get_possibilities (std::vector<int>& array, uint64& total_sum, int start, int end, int sum) {
    if (start == end) {
        cache[start][end] = array[start];
        total_sum += sum + array[start];
        return;
    }
    if (cache[start][end] != (unsigned int)(-1)) {
        total_sum += (unsigned int)std::pow(2,end-start)*sum + cache[start][end];
        return;
    }
    if (end == start + 1) {
        cache[start][end] = array[start] + array[end];
        total_sum += sum + array[start];
        total_sum += sum + array[end];
        return;
    }
    cache[start][end] = (unsigned int)std::pow(2,end-start)*sum + total_sum;
    get_possibilities(array, total_sum, start+2, end, sum+array[start]);
    get_possibilities(array, total_sum, start+1, end-1, sum+array[start]);
    get_possibilities(array, total_sum, start+1, end-1, sum+array[end]);
    get_possibilities(array, total_sum, start, end-2, sum+array[end]);
    cache[start][end] = total_sum - cache[start][end];
}

int main() {
    std::vector<int> v;
    v.reserve(2001);
    int T, N;
    uint64 sum;
    std::cin >> T;
    while (T--) {
        for (auto& c : cache) {
            c.fill((unsigned int)(-1));
        }
        std::cin >> N;
        v.resize(N);
        for (auto& e : v) {
            std::cin >> e;
        }
        sum = 0;
        get_possibilities(v, sum, 0, v.size()-1, 0);
        printf("%.3f\n", sum/std::pow(2,v.size()-1) );
    }
    return 0;
}