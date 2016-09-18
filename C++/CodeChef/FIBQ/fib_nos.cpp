#include <iostream>

using uint64 = long long int;

void fibo (int a, int b) {
    if ((a + b) < 1E9 + 3) {
        std::cout << a+b << ", ";
        fibo (b, a+b);
    }
}

int main() {
    uint64 a = 1, b = 2;
    std::cout << a << ", " << b << ", ";
    fibo(a, b);
    return 0;
}