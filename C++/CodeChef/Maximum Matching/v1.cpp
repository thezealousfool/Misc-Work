#include <iostream>
#include <string>
#include <vector>
#include <cmath>

using namespace std;

typedef long long int Int;

Int M;

vector<int> compute_max_number(const string &Str, int no_of_I) {
	vector<int> number(Str.length()+1);
	number[0] = Str.length() + 1 - no_of_I;
	int if_I = number[0] + 1;
	int if_D = number[0] - 1;
	for(int i=0; i<Str.length(); ++i) {
		if(Str.at(i)=='I') {
			number[i+1] = if_I;
			++if_I;
		}
		else {
			number[i+1] = if_D;
			--if_D;
		}
	}
	return number;
}

void calculate_ans(vector<int> &number, Int &sum) {
	Int value = 0;
	for(int i=0; i<number.size(); ++i) {
		for(int j=i+1; j<number.size(); ++j) {
			if(number[i]>number[j])
				++value;
		}
	}
	sum += ((Int)pow(value%M,2))%M;
}

void print_v(const vector<int>& v, const string& s) {
	cout<<s<<endl;
	for(int i=0; i<v.size(); ++i)
		cout<<v[i]<<" ";
	cout<<endl<<endl;
}

void compute(int &N) {
	--N;
	string s;
	s.reserve(N);
	for(int i=0; i<N; ++i)
		s.append("I");
	s.at(0)='D';
	Int sum=0;
	vector<int> v = compute_max_number(s,N-1);
	print_v(v,s);
	calculate_ans(v,sum);
	for(int j=1; j<N; ++j) {
		s.at(j)='D';
		s.at(j-1)='I';
		v = compute_max_number(s,N-1);
		print_v(v,s);
		calculate_ans(v,sum);
	}
	s.at(N-1)='I';
	for(int i=0; i<N; ++i) {
		s.at(i)='D';
		for(int j=i+1; j<N; ++j) {
			s.at(j)='D';
			v = compute_max_number(s,N-2-i);
			print_v(v,s);
			calculate_ans(v,sum);
			s.at(j)='I';
		}
	}
	s.at(N-1)='I';
	v = compute_max_number(s,1);
	print_v(v,s);
	calculate_ans(v,sum);
	cout<<sum<<endl;
}

int main() {
	int T;
	cin>>T;
	cin>>M;
	while(T--) {
		int N;
		cin>>N;
		compute(N);
	}
	return 0;
}