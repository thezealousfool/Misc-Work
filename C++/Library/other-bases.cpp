/*input
10
*/
#include <iostream>
#include <iomanip>
int main() {
	int n;
	std::cin>>n;

	// base = 8
	std::cout.setf(std::ios::oct, std::ios::basefield);
	std::cout<<n<<std::endl;

	// base = 16
	std::cout.setf(std::ios::hex, std::ios::basefield);
	std::cout<<n<<std::endl;

	// base = 10
	std::cout.setf(std::ios::dec, std::ios::basefield);
	std::cout<<n<<std::endl;

	// one-liner (requires iomanip)
	std::cout<<std::setbase(8)<<n<<std::endl<<std::setbase(10);
	
	return 0;
}