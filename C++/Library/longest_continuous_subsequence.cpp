/*input
10
1 2 3 9 10 2 3 7 9 15
*/
#include <iostream>
#include <vector>

int main() {
    int N;
    std::cin >> N;
    std::vector <int> array(N);
    for (auto& elem : array)
        std::cin >> elem;
    std::vector <int> longest_subsequence(N, 1);
    int max = 0;
    for (int i = 1; i < N; ++i) {
        if (array[i] > array[i-1]) {
            longest_subsequence[i] = longest_subsequence[i-1] + 1;
        }
        if (longest_subsequence[i] > longest_subsequence[max]) {
            max = i;
        }
    }
    for (int i = max - longest_subsequence[max] + 1; i <= max; ++i) {
        std::cout << array[i] << " ";
    }
    std::cout << "\n";
    return 0;
}