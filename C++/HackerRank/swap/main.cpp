#include <iostream>

using namespace std;


void swap2objs (auto& a, auto& b)
{
    auto k = a;
    a=b;
    b=k;
}

int main()
{
    char a='a',b='b';
    cout<<a<<endl<<b;
    cout<<endl<<endl;
    swap2objs(a,b);
    cout<<a<<endl<<b;
}
