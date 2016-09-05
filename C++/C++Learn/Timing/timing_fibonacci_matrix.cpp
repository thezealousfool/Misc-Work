/*input
1 50000
*/

// input : 15               time : 32 milliseconds
// input : 1500           time : 27 milliseconds
// input : 1500000     time : 28 milliseconds

#include <iostream>
#include <vector>
#include <array>
#include <chrono>

typedef long long int Int;
typedef std::array<std::array<Int, 2>, 2> matrix;

const std::array<Int, 2> void_array= {0, 0};
const Int Mod = 1E9 + 7;
const int K = 2;
const Int store_max = 1E7 + 1;

std::array <matrix, store_max> stored_values;
std::array <bool, store_max> calculated;

inline matrix multiply_matrix (const matrix& A, const matrix& B) {
    matrix C;
    C.fill(void_array);
    for (int i=0; i<K; ++i) {
        for (int j=0; j<K; ++j) {
            for (int k=0; k<K; ++k) {
                C[i][j] = (C[i][j] + A[i][k] * B[k][j]) % Mod;
            }
        }
    }
    return C;
}

inline matrix exponent_matrix (const matrix& A, Int power) {
    if (power==1)
        return A;
    if (power >= store_max) {
        if (power%2) {
            return multiply_matrix(A, exponent_matrix(A, power-1));
        }
        matrix X = exponent_matrix(A, power/2);
        return multiply_matrix(X, X);
    }
    if (calculated[power-1])
        return stored_values[power-1];
    if (power%2) {
        stored_values[power-1] = multiply_matrix(A, exponent_matrix(A, power-1));
        calculated[power-1] = true;
        return stored_values[power-1];
    }
    matrix X = exponent_matrix(A, power/2);
    stored_values[power-1] = multiply_matrix(X, X);
    calculated[power-1] = true;
    return stored_values[power-1];
}

inline Int Nth_fibonacci (const Int& N) {
    std::array<Int, K> F1;
    F1[0] = 1;
    F1[1] = 1;

    matrix T;
    T[0][0] = 0; T[0][1] = 1; T[1][0] = 1; T[1][1] = 1;

    if (N==1)
        return 1;
    T = exponent_matrix(T, N-1);

    Int result = 0;
    for (int i=0; i<K; ++i) {
        result = (result + T[0][i]*F1[i]) % Mod;
    }
    return result;
}

int main() {
    std::chrono::steady_clock::time_point start = std::chrono::steady_clock::now();
    stored_values[0][0][0] = 0; stored_values[0][0][1] = 1; stored_values[0][1][0] = 1; stored_values[0][1][1] = 1;
    calculated.fill(false);
    calculated[0] = true;
    Int n, m;
    std::cin >> n >> m;
    for (Int i=n; i<=m; ++i)
        std::cout << Nth_fibonacci(i) << std::endl;
    std::chrono::steady_clock::duration time = std::chrono::steady_clock::now() - start;
    std::cout << "Time taken: " << std::chrono::duration_cast<std::chrono::milliseconds>(time).count() << " milliseconds" << std::endl;
    return 0;
}