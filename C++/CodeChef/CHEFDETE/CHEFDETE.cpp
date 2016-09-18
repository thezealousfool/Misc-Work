/*input
6
0 1 1 2 2 3
*/
#include <iostream>
#include <vector>

typedef long long int Int;

int main()
{
        Int N;
        std::cin >> N;
        std::vector<bool> reports(N, false);
        for (Int i = 0; i < N; ++i)
        {
                Int temp;
                std::cin >> temp;
                if (temp == 0) {
                        continue;
                }
                --temp;
                if (!reports[temp])
                {
                        reports[temp] = true;
                }
        }
        for (Int i = 0; i < N; ++i)
        {
                if (!reports[i])
                {
                        std::cout << (i+1) << " ";
                }
        }
        return 0;
}
