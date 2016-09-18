#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
int nearest (int& no) {
	if(no<4) return 1;
	else if (no<5) return 4;
	else if (no<9) return 5;
	else if (no<10) return 9;
	else if (no<40) return 10;
	else if (no<50) return 40;
	else if (no<90) return 50;
	else if (no<100) return 90;
	else if (no<400) return 100;
	else if (no<500) return 400;
	else if (no<900) return 500;
	else if (no<1000) return 900;
	else return 1000;
}
void compute() {
	cout<<"Enter No: ";
	int no,tmp;
	cin>>no;
	vector<char> outV{};
	while (no>0) {
		tmp = nearest(no);
		switch (tmp) {
			case 1 : outV.push_back('I'); break;
			case 5 : outV.push_back('V'); break;
			case 10 : outV.push_back('X'); break;
			case 50 : outV.push_back('L'); break;
			case 100 : outV.push_back('C'); break;
			case 500 : outV.push_back('D'); break;
			case 1000 : outV.push_back('M'); break;
			case 4 : outV.push_back('I'); outV.push_back('V'); break;
			case 9 : outV.push_back('I'); outV.push_back('X'); break;
			case 40 : outV.push_back('X'); outV.push_back('L'); break;
			case 90 : outV.push_back('X'); outV.push_back('C'); break;
			case 400 : outV.push_back('C'); outV.push_back('D'); break;
			case 900 : outV.push_back('C'); outV.push_back('M'); break;
		}
		no -= tmp;
	}
	for_each(outV.begin(),outV.end(),[](char ch){cout<<ch;});
	cout<<endl;
}
int main() {
	int n;
	cin>>n;
	for(int i = 0; i<n; i++) {
		compute();
	}
	return 0;
}