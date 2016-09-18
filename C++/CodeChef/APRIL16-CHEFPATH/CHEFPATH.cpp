/*input
2
1000000000000000000 5
4 1
*/
#include <iostream>

typedef unsigned long long int uInt;
typedef long long int Int;

int main() {
    Int T;
    uInt N, M;
    std::cin >> T;
    while (T--) {
        std::cin >> N >> M;
        if (N==1 && M==1) {
            std::cout << "No" << std::endl;
            continue;
        }
        if ((N==1 && M==2) || (N==2 && M==1)) {
            std::cout << "Yes" << std::endl;
            continue;
        }
        if ((N==1) || (M==1)) {
            std::cout << "No" << std::endl;
            continue;
        }
        if (N%2==0 || M%2==0)
            std::cout << "Yes" << std::endl;
        else
            std::cout << "No" << std::endl;
    }
    return 0;
}