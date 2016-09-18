#include<cstdio>
int readInt()
{ int i=1;
  int cc = getchar_unlocked( );
  for (;(cc < '0' || cc > '9')&&cc!='-';)  cc = getchar_unlocked( ); //ignores char stream other than 0-9.
    int ret = 0;
    if(cc=='-'){
      i=-1;
      cc=getchar_unlocked();
    }
    for (;cc >= '0' && cc <= '9';) // if stream of numbers comes, start taking input
    {
      ret = ret * 10 + cc - '0'; // convert each char to integral digit and extend the final number
      cc = getchar_unlocked( );          // input continues
    }
    return (i*ret);                   // return final extended number.
  }
  #include<iostream>
  using namespace std;
  int main(){
    int T;
    T=readInt();
    for(int t=0;t<T;++t){
      int N;
      N=readInt();
      char Q[N+1];
      char C[N+1];
      scanf("%s",Q);
      scanf("%s",C);
      int W[N+1];
      for(int i=0;i<=N;++i){
        W[i]=readInt();
      }
      int max=0,min=0;
      for(int i=0;i<N;++i){
        if(C[i]==Q[i]){
          max++;
        }
      }
      int max_W=0;
      if(max!=N)
        for(int i=min;i<=max;++i){
          if(max_W<W[i]){
            max_W=W[i];
          }
        }
        else
          max_W=W[N];
          printf("%d\n",max_W);
        }
} 