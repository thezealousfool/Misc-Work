#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
using namespace std;

const static long int len = 100000;
int res[len];


void initArray (){
	for (int i=0; i<len; i++) {
	        res[i]=-1;
	    }
	res[len-1]=1;
}

void product (int i){
	int j=len-1;
	int carry=0;
	int temp=1;
	while(res[j]!=-1 || carry!=0){
		if(res[j]==-1)
			res[j]=0;
		temp=res[j]*i+carry;
		res[j]=temp%10;
		carry=temp/10;
		j--;
	}
}

int main() {
    initArray();
    int input;
    cin>>input;
    for (int i=input; i>=1; i--) {
        product(i);
    }
    for (int i=0; i<len; i++) {
        if(res[i]!=-1)
            cout<<res[i];
    }
}
