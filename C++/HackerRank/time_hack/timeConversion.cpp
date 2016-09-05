/*
 * timeConversion.cpp
 *
 *  Created on: 07-Oct-2015
 *      Author: vivu
 */

#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#include <iomanip>
using namespace std;


int main() {
    /* Enter your code here. Read input from STDIN. Print output to STDOUT */
    char input[20];
    gets(input);
    int hrs=0,mins=0,secs=0;
    char tmp[3];
    tmp[0]=input[0];
    tmp[1]=input[1];
    hrs = atoi(tmp);
    tmp[0]=input[3];
    tmp[1]=input[4];
    mins = atoi(tmp);
    tmp[0]=input[6];
    tmp[1]=input[7];
    secs = atoi(tmp);
    if(input[8]=='P' || input[8]=='p')
        hrs+=12;
    if(hrs<10)
        cout<<"0";
    cout<<hrs<<":";
     if(mins<10)
        cout<<"0";
    cout<<mins<<":";
     if(secs<10)
        cout<<"0";
    cout<<secs;
    return 0;
}
