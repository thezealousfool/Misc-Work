/*input
3
ab
bb
baaba
*/
#include <iostream>
#include <string>

int main() {
	std::string colors;
	int T, amber_no, brass_no;
	std::cin>>T;
	while (T--) {
		amber_no = brass_no = 0;
		std::cin>>colors;
		for(const char& c : colors)
			if (c == 'a')
				++amber_no;
			else
				++brass_no;
		std::cout<<((amber_no<brass_no)?amber_no:brass_no)<<std::endl;
	}
	return 0;
}