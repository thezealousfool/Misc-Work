/*input
11
-7 10 9 2 3 8 8 1 10 7 15
*/
#include <iostream>
#include <vector>

void print_path (std::vector<int>& array, std::vector<int>& subsequence_path, int max_index) {
    if (max_index == 0) {
        std::cout << array[max_index] << " ";
        return;
    }
    print_path(array, subsequence_path, subsequence_path[max_index]);
    std::cout << array[max_index] << " ";
}

int main() {
    int N;
    std::cin >> N;
    std::vector <int> array(N);
    for (auto& elem : array)
        std::cin >> elem;
    std::vector <int> longest_subsequence(N, 1);
    std::vector <int> subsequence_path(N);
    int max_index = 0;
    for (int i = 1; i < N; ++i) {
        for (int j = 0; j < i; ++j) {
            if (array[j] < array[i]) {
                if (1+longest_subsequence[j] > longest_subsequence[i]) {
                    longest_subsequence[i] = 1+longest_subsequence[j];
                    subsequence_path[i] = j;
                }
                if (longest_subsequence[i] > longest_subsequence[max_index]) {
                    max_index = i;
                }
            }
        }
    }
    print_path(array, subsequence_path, max_index);
    std::cout << "\n";
    return 0;
}