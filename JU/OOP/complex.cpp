#include <iostream>
#include <ostream>
#include <istream>

class complex_no {

	double r, i;

	public:
	complex_no()
	{
		set_values(0.0, 0.0);
	}

	complex_no(double real, double imaginary)
	{
		set_values(real, imaginary);
	}

	void set_values(double real, double imaginary)
	{
		r = real;
		i = imaginary;
	}

	friend std::ostream& operator<<(std::ostream& s, const complex_no& c1)
	{
		if(c1.r != 0 && c1.i != 0)
			s << c1.r << " + i" << c1.i;
		else if(c1.i == 0)
			s << c1.r;
		else if(c1.r == 0)
			s << "i" << c1.i;
		return s;
	}

	friend std::istream& operator>>(std::istream& s, complex_no& c1)
	{
		char temp;
		bool minus = false;
		s >> c1.r;
		s >> temp;
		
		if(temp == '-')
			minus = true;
		else if(temp == '+')
			minus = false;
		else
			return s;

		s >> temp;
		if(temp != 'i')
			return s;
		
		s >> c1.i;

		if(minus)
			c1.i *= -1;
		
		return s;
	}

	friend complex_no operator+(const complex_no& c1, const complex_no& c2)
	{
		complex_no c3(c1.r + c2.r, c1.i + c2.i);
		return c3;
	}

	friend complex_no operator-(const complex_no& c1, const complex_no& c2)
	{
		complex_no c3(c1.r - c2.r, c1.i - c2.i);
		return c3;
	}

};

int main(void)
{
	std::cout << "Complex Number:\n";
	std::cout << "1. Initialise\n";
	std::cout << "2. Add\n";
	std::cout << "3. Substract\n";
	std::cout << "4. Exit\n";

	while(true) {
		int choice;
		complex_no c1, c2, c3;
		std::cout << "Enter choice: ";
		std::cin >> choice;
		switch(choice) {
			case 1:
				std::cout << "Complex No: ";
				std::cin >> c1;
				std::cout << "Input successful!\n" << c1 << "\n";
				break;
			case 2:
				std::cout << "Complex No 1: ";
				std::cin >> c1;
				std::cout << "Complex No 2: ";
				std::cin >> c2;
				c3 = c1 + c2;
				std::cout << "Addition successful!\nResult: " << c3 << "\n";
				break;
			case 3:
				std::cout << "Complex No 1: ";
				std::cin >> c1;
				std::cout << "Complex No 2: ";
				std::cin >> c2;
				c3 = c1 - c2;
				std::cout << "Substraction successful!\nResult: " << c3 << "\n";
				break;
			case 4:
				break;
			default:
				std::cout << "Wrong Input\n";
				break;
		}
		if(choice == 4)
			break;
	}
	return 0;
}