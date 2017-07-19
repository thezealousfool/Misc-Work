#include <iostream>
#include <vector>
#include <cstdio>
#include <cstdlib>

#define max(a, b) (a) > (b) ? (a) : (b);
typedef long long int Int;

Int find_sols(std::vector<Int>& inp_v, Int K, Int ord) {
    if ((!K) || (ord == inp_v.size())) {
        if (K)
            return 0;
        Int res = 0;
        for (Int loop = 0; loop < inp_v.size(); ++loop) {
            if (!inp_v[loop])
                ++res;
        }
        return res;
    }
    Int res1, res2;
    for (Int loop = 0; loop < inp_v.size(); ++loop) {
        if (!(inp_v[loop] & (1 << ord))) {
            inp_v[loop] = inp_v[loop] & (!(1 << ord));
        }
        else {
            inp_v[loop] = inp_v[loop] | (1 << ord);
        }
    }
    res1 = find_sols(inp_v, K-1, ord+1);
    for (Int loop = 0; loop < inp_v.size(); ++loop) {
        if ((inp_v[loop] & (1 << ord))) {
            inp_v[loop] = inp_v[loop] & (!(1 << ord));
        }
        else {
            inp_v[loop] = inp_v[loop] | (1 << ord);
        }
    }
    res2 = find_sols(inp_v, K, ord+1);
    return max(res1, res2);
}

int main() {
    Int T;
    std::cin >> T;
    while (T--) {
        Int N, M, K;
        std::cin >> N >> M >> K;
        char *inp = new char[M];
        char *endpointer;
        std::vector<Int> inp_v(N);
        K = (K - M)%2 ? (M-1) : M;
        getchar();
        for(int i = 0; i < N; ++i) {
            for (int i2 = 0; i2 < M; ++i2) {
                inp[i2] = getchar();
                getchar();
            }
            inp_v[i] = strtol(inp, &endpointer, 2);
        }
        std::cout << find_sols(inp_v, K, 0) << '\n';
        delete inp;
    }
    return 0;
}
