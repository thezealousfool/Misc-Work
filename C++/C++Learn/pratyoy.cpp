#include <iostream>
typedef long long int Int;

Int factor_count(Int n)
{
	Int count = 0;
	for(Int i = 2; i < n; ++i) {
		if(n % i == 0) {
			++count;
			n /= i;
		}
	}
	return count;
}

int main(void)
{
	Int T;
	std::cin >> T;
	while(T--) {
		Int N, result = 0;
		std::cin >> N;
		while(N--) {
			Int a;
			std::cin >> a;
			if((N % 2) == 0)
				result += (factor_count(a) - 1);
			else
				result += ((factor_count(a) - 1) * 4);
			result %= 5;
		}
		if(result == 0)
			std::cout << "B\n";
		else
			std::cout << "A\n";
	}
	return 0;
}