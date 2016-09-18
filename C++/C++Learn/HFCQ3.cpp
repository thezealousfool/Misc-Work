#include<bits/stdc++.h>
using namespace std;
typedef long long int uli;
uli f[234][123][123][4];
const uli mod=1e9+7;
uli solve(int b,int n,int p,int z){
   if(p<=0)return 1;
   if(b==0)return 0;
 
   uli &fi=f[b][n][p][z];
   if(fi!=-1)return fi;
 
   fi=0;
   if(n!=0){
      fi+=solve(b,n-1,p,z);
      fi+=solve(b,n-1,p-1,z);
      fi+=solve(b,n-1,p-2,z);
      fi+=solve(b,n-1,p-4,z);
      fi+=solve(b,n-1,p-6,z);
   }
   if(b!=0){
      if(z!=2)fi+=solve(b-1,n,p,z+1);
      fi+=solve(b-1,n,p-1,0); 
      fi+=solve(b-1,n,p-2,0); 
      fi+=solve(b-1,n,p-4,0); 
      fi+=solve(b-1,n,p-6,0); 
   }
   fi%=mod;
   return fi;
}
int main(){
   int t,b,n;
   scanf("%d",&t);
   memset(f,-1ll,sizeof f);
   while(t--){
      scanf("%d %d",&b,&n);
      uli ans=solve(b,n,100,0);
      printf("%lld\n",ans);
   }
   return 0;
}