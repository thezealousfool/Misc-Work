/*input
5
1 2 3 4 5
*/
#include <iostream>

int main() {
	int t, odd_no, even_no;
	std::cin>>t;
	odd_no = even_no = 0;
	while (t--) {
		int temp;
		std::cin>>temp;
		if (temp%2 == 0)
			++even_no;
		else
			++odd_no;
	}
	if (even_no>odd_no)
		std::cout<<"READY FOR BATTLE"<<std::endl;
	else
		std::cout<<"NOT READY"<<std::endl;
	return 0;
}