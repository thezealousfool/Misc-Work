/*input
1 200 35
4 5 62
7 8 91
*/
#include <iostream>
using namespace std;
int main() {
	double i[9];
	for(int k=0; k<9; ++k) {
		cin>>i[k];
	}
	double determinant = 0;
	determinant = (i[0]*(i[4]*i[8] - i[5]*i[7]) - i[1]*(i[3]*i[8] - i[5]*i[6]) + i[2]*(i[3]*i[7] - i[4]*i[6]));
	cout<<endl<<determinant<<endl;
	return 0;
}