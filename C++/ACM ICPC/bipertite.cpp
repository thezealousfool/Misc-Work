#include <iostream>
#include <vector>
using namespace std;	
			
int main(){
	int n,m,t,d,D;
	cin >> t;
	while(t--){
		cin >> n >> m >> d >> D;
		if(m<(n*d) || m>n*D){
			cout<<"-1\n";
		}
		else {
			for(int i = 1; i <= n; ++i) {
				for(int j = 0; j < d; ++j) {
					std::cout << i << " " << i+j << "\n";
				}
			}
			int c;
			c = (m-n*d)/n;
			for(int i = 1; i <= n && m > 0; ++i) {
				for(int j = 0; j < c; ++j) {
					std::cout << i << " " << i+j << "\n";
				}
			}
			c = m - n*d - n*c;
			for(int i = 1; i <= c; ++i) {
				std::cout << i << " " << i << "\n";
			}
		}
	}
	return 0;
}
