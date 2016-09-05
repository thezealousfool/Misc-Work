#include <iostream>
#include <chrono>

typedef long long int Int;

int main() {
    // std::ios::sync_with_stdio(false);
    std::chrono::steady_clock::time_point start = std::chrono::steady_clock::now();
    for (Int i=0; i<=(Int)1E4; ++i)
        std::cout << i << "\n";
    std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();
    std::chrono::steady_clock::duration time = end - start;
    //std::cout << std::chrono::duration_cast<std::chrono::milliseconds>(time).count() << " milliseconds" << std::endl;
     std::cout << std::chrono::duration_cast<std::chrono::nanoseconds>(time).count() << std::endl;
    return 0;
}
