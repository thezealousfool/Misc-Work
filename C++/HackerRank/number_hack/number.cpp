/*
 * number.cpp
 *
 *  Created on: 07-Oct-2015
 *      Author: vivu
 */

#include <cmath>
#include <cstdio>
#include <iomanip>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;


int main() {
    /* Enter your code here. Read input from STDIN. Print output to STDOUT */
    int n=0,positive=0,negative=0;
    cin>>n;
    for(int i=0; i<n; i++) {
        int temp;
        cin>>temp;
        if(temp>0) {
            positive+=1;
        }
        else if (temp<0) {
            negative+=1;
        }
    }
    cout<<positive<<endl<<negative<<endl<<n<<endl;
    cout<<fixed<<setprecision(3)<<(positive/(double)n)<<endl<<(negative/(double)n)<<endl<<((n-positive-negative)/(double)n);
    return 0;
}
