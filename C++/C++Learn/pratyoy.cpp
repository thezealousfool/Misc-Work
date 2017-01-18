#include <iostream>

int factor_count(int n)
{
	int count = 0;
	for(int i = 2; i < n; ++i) {
		if(n % 2 == 0) {
			++count;
			n /= 2;
		}
	}
	return count;
}

int main(void)
{
	int T;
	std::cin >> T;
	while(T--) {
		int N, result = 0;
		std::cin >> N;
		while(N--) {
			int a;
			std::cin >> a;
			if(N & 1 == 0)
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