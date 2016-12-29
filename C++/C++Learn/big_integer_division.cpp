#include <iostream>
#include <string>
#include <utility>

bool remove_zero (std::string& s)
{
	if(s[0] == '0') {
		s.erase(s.begin());
		return true;
	}
	return false;
}

void subs (std::string& val, std::string& from)
{
	if(from < val)
		return;

	int len = val.length();
	
	while(len) {
	
		--len;
	
		if(from[len] < val[len]) {
			--from[len-1];
			from[len] += 10;
		}
	
		from[len] -= val[len] - '0';
	}
}

std::pair<std::string, std::string> divide (std::string divisor,
											std::string divident)
{
	std::string quotient = "";

	int iterations = divident.length() - divisor.length() + 1;

	while(iterations--) {
		if (divisor.length() > divident.length()) {
			quotient.push_back('0');
			break;
		}
		
		int val = 0;

		while(divisor < divident) {
			subs(divisor, divident);
			++val;
		}

		quotient.push_back('0' + val);
		if(remove_zero(divident))
			continue;
		if(!val) {
			divisor = "0" + divisor;
		}
	}

	while(remove_zero(divident));
	while(remove_zero(quotient));
	if(divident=="")
		divident="0";
	if(quotient=="")
		quotient="0";

	return std::make_pair(quotient, divident);
}

int main(void)
{
	std::string divisor, divident;

	std::cout << "Enter Divisor: ";
	std::cin >> divisor;
	std::cout << "Enter Divident: ";
	std::cin >> divident;
	std::cout << "\n";

	std::pair<std::string, std::string> result = divide (divisor, divident);

	std::cout << "Quotient: " << result.first << "\n";
	std::cout << "Remainder: " << result.second << "\n";

	return 0;
}