/*input
ACB
*/
#include <iostream>
#include <string>
#include <algorithm>

int main() {
    std::string input;
    std::cin >> input;
    std::sort(input.begin(), input.end());
    do {
        std::cout << input << "\n";
    }
    while (std::next_permutation(input.begin(), input.end()));
    return 0;
}