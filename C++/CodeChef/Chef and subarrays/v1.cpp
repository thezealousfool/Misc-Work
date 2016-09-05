#include <iostream>
#include <array>

using namespace std;

typedef long long int Int;

array<int,51> output;
array <Int,51> input;
array <Int,52> sum;
array <Int,52> product;

int compute() {
	int n,count;
	cin>>n;
	count = n;
	for(int i=0; i<n; ++i) {
		cin>>input[i];
		sum[i+1]=sum[i]+input[i];
		product[i+1]=product[i]*input[i];
	}
	for(int i=0; i<n; ++i) {
		for (int j=i+1; j<n; ++j) {
			if ((sum[j+1]-sum[i])==(product[j+1]/product[i]))
				++count;
		}
	}
	return count;
}

int main() {
	int T;
	cin>>T;
	sum[0]=0;
	product[0]=1;
	for (int i=0; i<T; ++i) {
		output[i]=compute();
	}
	for (int i=0; i<T; ++i) {
		cout<<output[i]<<endl;
	}
}