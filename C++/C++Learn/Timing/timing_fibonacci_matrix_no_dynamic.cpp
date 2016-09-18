/*input
1 50000
*/
#include <iostream>
#include <vector>
#include <chrono>

typedef long long int Int;
typedef std::vector<std::vector<Int>> matrix;

const Int Mod = 1E9 + 7;
const int K = 2;

inline matrix multiply_matrix (const matrix& A, const matrix& B) {
    matrix C(K, std::vector<Int>(K));
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
    if (power%2)
        return multiply_matrix(A, exponent_matrix(A, power-1));
    matrix X = exponent_matrix(A, power/2);
    return multiply_matrix(X, X);
}

inline Int Nth_fibonacci (const Int& N) {
    std::vector<Int> F1(K);
    F1[0] = 1;
    F1[1] = 1;

    matrix T(K, std::vector<Int> (K));
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
    Int n, m;
    std::cin >> n >> m;
    for (Int i=n; i<=m; ++i)
        std::cout << Nth_fibonacci (i) << std::endl;
    std::chrono::steady_clock::duration time = std::chrono::steady_clock::now() - start;
    std::cout << "Time taken: " << std::chrono::duration_cast<std::chrono::milliseconds>(time).count() << " milliseconds" << std::endl;
    
    return 0;
}