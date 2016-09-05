/*input
12
eededdeedede
*/
#include <iostream>
#include <string>

typedef long long int Int;

Int longestPalSubstr(const std::string& str, Int n)
{
    bool table[n][n];
    std::fill_n(&table[0][0], sizeof(table) / sizeof(bool), false);
    Int maxLength = 1;
    for (Int i = 0; i < n; ++i)
        table[i][i] = true;
    Int start = 0;
    for (Int i = 0; i < n-1; ++i)
    {
        if (str[i] == str[i+1])
        {
            table[i][i+1] = true;
            start = i;
            maxLength = 2;
        }
    }
    for (Int k = 3; k <= n; ++k)
    {
        for (Int i = 0; i < n-k+1 ; ++i)
        {
            Int j = i + k - 1;
            if (table[i+1][j-1] && str[i] == str[j])
            {
                table[i][j] = true;
                if (k > maxLength)
                {
                    start = i;
                    maxLength = k;
                }
            }
        }
    }
    return maxLength;
}

int main() {
    Int N;
    std::cin>>N;
    std::cin.get();
    std::string s;
    getline(std::cin, s);
    s = s+s;
    for (Int i=0; i<N; ++i) {
        std::string s1 = s.substr(i,N);
        std::cout<<longestPalSubstr(s1, N)<<std::endl;
    }
}
