/*input

*/
#include <iostream>
#include <vector>
#include <cstdlib>

using namespace std;

int no_of_days(int month, int year) {
	if( (month>0 && month<13) && (year>0 && year<10000) ) {
		switch(month) {
			case 1 : case 3 : case 5 : case 7 : case 8 : case 10 : case 12 : 
				return 31;
			case 4 : case 6 : case 9 : case 11 :
				return 30;
			case 2 :
				if(year%100==0) {
					if(year%4==0)
						return 29;
					else
						return 28;
				}
				else {
					if(year%4==0)
						return 29;
					else
						return 28;
				}
		}
	}
 return 0;
}

int main() {
	while(true) {
		system("clear");
		cout<<endl;
		string month_names[12] = {"JANUARY" , "FEBRUARY" , "MARCH" , "APRIL" , "MAY" , "JUNE" , "JULY" , "AUGUST" , "SEPTEMBER" , "OCTOBER" , "NOVEMBER" , "DECEMBER"};
		cout<<"Enter month[In numbers from 1-12]: ";
		int month;
		cin>>month;
		if(month>12 || month<1) {
			cout<<"Error: Wrong input!!";
			continue;
		}
		cout<<endl;
		cout<<"Enter year[4 digits]: ";
		int year;
		cin>>year;
		cout<<endl<<endl<<"\t"<<"********************CALENDER**********************"<<endl<<endl;
		cout<<"\t\t\t"<<month_names[month-1]<<", "<<year<<endl<<endl;
		int month_copy = month;
		int year_copy = year;
		if(month_copy > 2)
			month_copy -= 2;
		else {
			month_copy += 10;
			--year_copy;
		}
		int no_of_centuries = year_copy/100;
		int rest_years = year_copy%100;
		int day = (   1 + (  ( (13*month_copy)-1 ) / 5  )   +   (no_of_centuries/4) - (2*no_of_centuries) + rest_years + (rest_years/4)   ) % 7;
		if(day < 0)
			day += 7;
		cout<<"\tSun\tMon\tTue\tWed\tThu\tFri\tSat"<<endl;
		for(int i=0; i<=day; ++i)
			cout<<"\t";
		for(int i=1; i<=no_of_days(month,year); ++i) {
			cout<<i<<"\t";
			++day;
			day %= 7;
			if(day==0)
				cout<<endl<<"\t";
		}
		cout<<endl<<endl;
		cout<<"Enter 1 for more output trials, 2 to exit: ";
		int more;
		cin>>more;
		if(more!=1)
			break;
	}
	return 0;
}