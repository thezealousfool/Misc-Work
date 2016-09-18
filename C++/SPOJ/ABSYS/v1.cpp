#include <iostream>
#include <string>
#include <vector>
#include <cstdio>

using namespace std;

int main() {
	char inp[100];
	string n1,n2,res;
	int number1,number2,result;
	int T;
	cin>>T;
	vector<string> results(T);
	cin.get();
	for(int i=0; i<T; ++i) {
		number1 = number2 = result = -1;
		cin.get();
		scanf("%s",&inp);
		n1 = inp;
		cin.get();
		cin.get();
		cin.get();
		scanf("%s",&inp);
		n2 = inp;
		cin.get();
		cin.get();
		cin.get();
		scanf("%s",&inp);
		cin.get();
		res = inp;
		if(n1.find_first_of('m')==string::npos) 
			number1 = stoi(n1);
		if(n2.find_first_of('m')==string::npos)
			number2 = stoi(n2);
		if(res.find_first_of('m')==string::npos)
			result = stoi(res);
		if(number1!=-1) {
			results[i].append(n1);
			results[i].append(" + ");
		}
		else {
			results[i].append(to_string(result - number2));
			results[i].append(" + " + n2 + " = " + res);
			continue;
		}
		if(number2!=-1) {
			results[i].append(n2);
			results[i].append(" = ");
		}
		else {
			results[i].append(to_string(result - number1));
			results[i].append(" = " + res);
			continue;
		}
		if(result!=-1) {
			results[i].append(res);
		}
		else {
			results[i].append(to_string(number1 + number2));
			continue;
		}
	}
	for(int i=0; i<T; ++i)
		cout<<results[i]<<endl;
	return 0;
}