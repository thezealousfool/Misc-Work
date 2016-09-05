#include <iostream>
#include <array>
#include <string>
using namespace std;

int main() {
    int N, M;
    cin>>N>>M;
    array<array<bool, M>, N> p;
    for(int i = 0; i<N; ++i) {
        for(int j = 0; j<M; ++j) {
            p[i][j]=(int)(cin.get() - '0');
        }
    }
}