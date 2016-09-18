#include <iostream>
#include <vector>
#include <string>
using namespace std;

int main()
{
	int T;
	int year;
	cin>>T;
	vector<string> out(T);
	for(int i=0; i<T; ++i) {
		int day=1;
		cin>>year;
		int days=0;
		int yr = year<2001?year:2001;
		int yr_end = year<2001?2001:year;
		//cout<<yr<<"\t"<<yr_end<<endl;
		while(yr<yr_end) {
			++days;
			if((yr%400)==0)
				++days;
			else if((yr%100)!=0 && (yr%4)==0)
				++days;
			++yr;
		}
		if(yr_end==2001)
			day-=days;
		else
			day+=days;
		day%=7;
		if(day<0)
			day+=7;
		switch (day) {
			case 0 : out[i]="sunday"; break;
			case 1 : out[i]="monday"; break;
			case 2 : out[i]="tuesday"; break;
			case 3 : out[i]="wednesday"; break;
			case 4 : out[i]="thursday"; break;
			case 5 : out[i]="friday"; break;
			case 6 : out[i]="saturday"; break;
		}
	}
	for (int i = 0; i < T; ++i)
	{
		cout<<out[i]<<endl;
	}
	return 0;
}