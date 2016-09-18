#include <iostream>
#include <set>
#include <array>
#include <string>

using namespace std;

array<string,21> output;
array<string,101> search_input;
set<string> words {};

string compute() {
	string s = "";
	int N,K,L;
	cin>>N>>K;
	for(int i=0; i<N; ++i) {
		cin>>search_input[i];
	}
	for(int i=0; i<K; ++i) {
		cin>>L;
		for(int j=0; j<L; ++j) {
			string temp;
			cin>>temp;
			words.insert(temp);
		}
	}
	for(int i=0; i<N; ++i) {
		if(words.find(search_input[i])!=words.end())
			s += "YES ";
		else
			s += "NO ";
	}
	return s;
}

int main() {
	int T;
	cin>>T;
	for(int i=0; i<T; ++i) {
		output[i]=compute();
	}
	for(int i=0; i<T; ++i) {
		cout<<output[i]<<endl;
	}
	return 0;
}