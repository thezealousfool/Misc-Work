/*input
1
30 7
*/
#include <iostream>

typedef long long int Int;
typedef long double Dob;

const Int max = (Int)1E6;
Int pascal_triangle_row[max];

void populate_triangle(const Int &n) {
	pascal_triangle_row[0] = 1;
	for (Int i=1; i<=n; ++i) {
		pascal_triangle_row[i] = 0;
		for (Int j=i; j>0; --j)
			pascal_triangle_row[j] += pascal_triangle_row[j-1];
	}
}

Int recur (Int n, Int r) {
	if (n==r) return 1;
	if (r==1) return n;
	if (r==0) return 1;
	if (r>n/2) r = n-r;
	return recur(n-1, r) + recur(n-1, r-1);
}

Int C(Int n, Int r) {
	if (r>n/2) r = n-r;
	Int ans = 1;
	for (int i =1; i<=r; ++i) {
		ans *= n-r+i;
		ans /= i;
	}
	return ans;
}

int main() {
	int T;
	std::cin>>T;
	// Int stored_n = 1;
	// populate_triangle(stored_n);
	while (T--) {
		Int n, k;
		std::cin>>n>>k;
		--n; --k;
		/*if (n != stored_n) {
			stored_n = n;
			populate_triangle(stored_n);
		}
		std::cout<<pascal_triangle_row[k]<<std::endl;*/
		std::cout<<C(n,k)<<std::endl;
	}
	return 0;
}