/*input
100000 5
1 2 3
Q 1 2
Q 2 3
C 1 2
Q 1 2
Q 1 3
*/
#include <iostream>
#include <vector>

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

inline void add_element (const std::vector<Int>& input,const Int& index, Int& sum, Int& result, const Int& Y) {
    if (index==Y-1) {
        sum += input[index];
        result += Nth_fibonacci(sum);
        result %= Mod;
        sum -= input[index];
        return;
    }
    sum += input[index];
    for (Int i = index+1; i<Y; ++i) {
        add_element(input, i, sum, result, Y);
    }
    result += Nth_fibonacci(sum);
    result %= Mod;
    sum -= input[index];
    return;
}

int main() {
    Int N, M;
    std::cin >> N >> M;
    std::vector<Int> input(N);
    for (Int i=0; i<N; ++i) {
        std::cin >> input[i];
    }
    while (M--) {
        char choice; Int X, Y;
        std::cin >> choice >> X >> Y;
        if (choice == 'C')
            input[X-1] = Y;
        else {
            --X;
            Int sum = 0, result = 0;
            for (Int i=X; i<Y; ++i) {
                add_element(input, i, sum, result, Y);
            }
            std::cout << result << std::endl;
        }
    }
    return 0;
}