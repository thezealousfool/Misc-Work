#include <iostream>
#include <iomanip>

enum class am_pm
{
	am,
	pm,
	twenty_four_hour,
	twelve_hour
};

class my_time
{
	int h, m, s;

	void validate_time()
	{
		if(s >= 60) {
			m += int(s / 60);
			s %= 60;
		}
		if(m >= 60) {
			h += int(m / 60);
			m %= 60;
		}
		if(h >= 24) {
			h %= 24;
		}
	}

	public:
		my_time()
		{
			set_time(0, 0, 0);
		}

		my_time(int hrs, int mins, int secs, am_pm flag = am_pm::twenty_four_hour)
		{
			set_time(hrs, mins, secs, flag);
		}

		void set_time(int hrs, int mins, int secs, am_pm flag = am_pm::twenty_four_hour)
		{
			h = hrs;
			m = mins;
			s = secs;
			if(flag == am_pm::pm)
				h += 12;
			validate_time();
		}

		void print_time(am_pm flag = am_pm::twenty_four_hour)
		{
			bool pm_flag = false;
			if(flag == am_pm::twenty_four_hour) {
				std::cout << std::setfill('0') << std::setw(2) << h;
			}
			else if(flag == am_pm::twelve_hour) {
				if(h > 12) {
					std::cout << std::setfill('0') << std::setw(2) << h-12;
					pm_flag = true;
				}
				else if(h == 12) {
					std::cout << std::setfill('0') << std::setw(2) << h;
					pm_flag = true;
				}
				else {
					std::cout << std::setfill('0') << std::setw(2) << h;
				}
			}
			else {
				return;
			}
			std::cout << ":";
			std::cout << std::setfill('0') << std::setw(2) << m;
			std::cout << ":";
			std::cout << std::setfill('0') << std::setw(2) << s;
			if(flag != am_pm::twenty_four_hour) {
				if(pm_flag)
					std::cout << " pm";
				else
					std::cout << " am";
			}
			std::cout << "\n";
		}

		void add_time(int hrs, int mins, int secs) {
			h += hrs;
			m += mins;
			s += secs;
			validate_time();
		}
};

int main(void)
{
	std::cout << "Time:\n";
	std::cout << "1. 24 hours time\n";
	std::cout << "2. 12 hours time\n";
	std::cout << "3. Display time in 24 hours format\n";
	std::cout << "4. Display time in 12 hours format\n";
	std::cout << "5. Add time\n";
	std::cout << "6. Exit\n";
	my_time t;
	while(true) {
		int choice;
		std::cout << "Enter choice: ";
		std::cin >> choice;
		int h, m, s; char ap;
		switch(choice) {
			case 1:
				t.set_time(0, 0, 0); 
				std::cout << "Enter time as hh:mm:ss\n";
				scanf("%d:%d:%d", &h, &m, &s);
				t.set_time(h, m, s);
				break;
			case 2:
				t.set_time(0, 0, 0); 
				std::cout << "Enter time as hh:mm:ss\n";
				scanf("%d:%d:%d", &h, &m, &s);
				if(h > 12) {
					std::cout << "Invalid input for 12 hour clock!\n";
					break;
				}
				std::cout << "Enter a for AM p for PM\n";
				std::cin >> ap;
				if(ap == 'a') {
					t.set_time(h, m, s, am_pm::am);
				} 
				else if(ap == 'p') {
					t.set_time(h, m, s, am_pm::pm);
				}
				else {
					std::cout << "Wrong Input\n";
				}
				break;
			case 3:
				t.print_time(am_pm::twenty_four_hour);
				break;
			case 4:
				t.print_time(am_pm::twelve_hour);
				break;
			case 5:
				std::cout << "Enter time as hh:mm:ss\n";
				scanf("%d:%d:%d", &h, &m, &s);
				t.add_time(h, m, s);
				break;
			case 6:
				break;
			default:
				std::cout << "Wrong Input\n";
				break;
		}
		if(choice == 6)
			break;
	}
	return 0;
}