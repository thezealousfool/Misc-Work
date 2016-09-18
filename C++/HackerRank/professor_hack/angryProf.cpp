#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

int N=0,K=0,t[1000],rec=0;


void initArray(int n) {
    for(;n>=0;n--){
        t[n]=0;
    }
}

void init() {
	N=0;K=0;initArray(1000);rec=0;
}

void input() {
    cin>>N>>K;
    initArray(N);
    for (int i=0; i<N; i++)
        cin>>t[i];
}

int compute() {
    for (int i=0; i<N; i++) {
        if(t[i]==0 || t[i]<0)
            rec++;
    }
    if (rec>=K)
        return 0;
    else
        return 1;
}

int main() {
    /* Enter your code here. Read input from STDIN. Print output to STDOUT */
    int no=0;
    cin>>no;
    int result[11];
    for(int i=0; i<no; i++) {
    	init();
        input();
        result[i]=compute();
    }
    for(int i=0; i<no; i++) {
        if(result[i])
            cout<<"YES"<<endl;
        else
            cout<<"NO"<<endl;
    }
    return 0;
}
