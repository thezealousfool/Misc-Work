/*input
3
3
RGR
3
RRR
3
RGB
*/
#include <iostream>
#include <vector>
#include <string>

typedef long long int Int;

int main() {
    int T;
    Int N, R_count, B_count, G_count, result;
    char max;
    std::string s;
    std::cin >> T;
    while (T--) {
        R_count = B_count = G_count = 0;
        std::cin >> N;
        std::cin.get();
        std::getline(std::cin, s);
        for (Int i=0; i<N; ++i) {
            switch (s[i]) {
                case 'R' : ++R_count; break;
                case 'G' : ++G_count; break;
                case 'B' : ++B_count; break; 
            }
        }
        result = 0;
        if (R_count > G_count) {
            if (G_count > B_count)
                max = 'R';
            else {
                if (R_count > B_count)
                    max = 'R';
                else
                    max = 'B';
            }
        }
        else {
            if (R_count > B_count)
                max = 'G';
            else {
                if (G_count > B_count)
                    max = 'G';
                else
                    max = 'B';
            }
        }
        for (Int i=0; i<N; ++i) {
            if (s[i]!=max)
                ++result;
        }
        std::cout << result << std::endl;
    }
    return 0;
}