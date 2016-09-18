/*input
1100100
*/
#include <iostream>
#include <bitset>

int main() {
	// input a binary number of length 35 digits:
	//
	std::bitset<35> temp;
	std::cin>>temp;
		
	// to print the decimal equivalent of a binary (bitset)
	std::cout<<temp.to_ulong()<<std::endl;

	// input a int and convert it to binary (bitset)
	// 
	// int i;
	// std::cin>>i;
	// std::bitset<50> temp(i);

	// to print the binary as a string
	// std::cout<<temp.to_string()<<std::endl;

	// accessing a perticular bit (right to left)
	// std::cout<<temp[5]<<std::endl;

	return 0;
}