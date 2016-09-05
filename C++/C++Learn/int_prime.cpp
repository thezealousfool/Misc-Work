/*input
12
*/
#include <iostream>
#include <cmath>

using namespace std;

typedef long long int Int;
typedef long double Dob;

int main() {
	int n;
	cin>>n;
	int count=0, ans=0;
	while(n%2==0) {
		++count;
		n /= 2;
	}
	if(count>0)
		ans = count+1;
	for(int i=3; (i<=n && n>2); i += 2) {
		count = 0;
		while(n%i==0) {
			++count;
			n /= i;
		}
		if(count>0){
			if(ans==0)
				ans=1;
			ans *= count+1;
		}
	}
	cout<<ans<<endl;
	return 0;
}