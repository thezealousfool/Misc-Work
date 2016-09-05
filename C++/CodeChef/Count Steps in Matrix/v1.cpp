#include <iostream>
#include <array>

using namespace std;

struct coordinates {
	int x, y;
};

long long int ans;
coordinates position[251001];
long long int answers[6];
int N;

void compute_answer() {
	ans=0;
	for (int i = 1; i<N*N; ++i) {
		ans += abs(position[i+1].x - position[i].x) + abs(position[i+1].y - position[i].y);
	}
}

int main() {
	int T;
	int i,j,k,temp;
	cin>>T;
	for (i=0; i<T; ++i) {
		cin>>N;
		for (j=0; j<N; ++j) {
			for (k=0; k<N; ++k) {
				cin>>temp;
				position[temp] = {j,k};
			}
		}
		compute_answer();
		answers[i] = ans;
	}
	for (i=0; i<T; ++i)
		cout<<answers[i]<<endl;
	return 0;
}