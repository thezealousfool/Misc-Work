#include <iostream>
#include <sstream>
#include <chrono>

typedef long long int Int;

int main() {
    std::chrono::steady_clock::time_point start = std::chrono::steady_clock::now();
    std::ios_base::sync_with_stdio(false);
    std::stringbuf buffer(std::ios::out);
    std::ostream cout(&buffer);
    for (Int i=0; i<(Int)1E6; ++i)
        cout << i << "\n";
    std::cout << buffer.str();
    std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();
    std::chrono::steady_clock::duration time = end - start;
    std::cout << std::chrono::duration_cast<std::chrono::milliseconds>(time).count() << " milliseconds" << std::endl;
    return 0;
}