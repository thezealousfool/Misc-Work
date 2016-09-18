/*input
3 5
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

const Int Mod = 1E9 + 7;

std::vector<Int> fibonacci_terms(1E7 + 1, -1);

Int Nth_fibonacci (const Int& N) {
    if (fibonacci_terms[N-1]!=-1)
        return fibonacci_terms[N-1];
    fibonacci_terms[N-1] = (Nth_fibonacci(N-1) + Nth_fibonacci(N-2)) % Mod;
    return fibonacci_terms[N-1];
}

void add_element (const std::vector<Int>& input,const Int& index, Int& sum, Int& result, const Int& Y) {
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
    fibonacci_terms[0] = fibonacci_terms[1] = 1;
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