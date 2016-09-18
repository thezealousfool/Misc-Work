#include<bits/stdc++.h>
using namespace std;
typedef long long int uli;
const int mx=5000;
int N;
int dir[8][2];
set<pair<int,int> >vis;
vector<int>cycle;
map<pair<int,int>,int>mp;
bool check(vector<int>_a,vector<int>_b){
   vector<int>a,b;
   for(int i=0;i<(int)_a.size();i++){
      if(_a[i]!=-1)a.push_back(_a[i]);
   }
   for(int i=0;i<(int)_b.size();i++){
      if(_b[i]!=-1)b.push_back(_b[i]);
   }
 
 
   int n=a.size();
   for(int i=0;i<=n;i++){
      if(a==b)return true;
      for(int j=1;j<n;j++)swap(a[j],a[j-1]);
   }
   return false;
}
void dfs(int r,int c){
   cycle.push_back(mp[make_pair(r,c)]);
   vis.insert(make_pair(r,c));
   for(int i=0;i<8;i++){
      int nr=r+dir[i][0];
      int nc=c+dir[i][1];
      if(0<=nr && nr<N && 0<=nc && nc<N && !vis.count(make_pair(nr,nc)) ){
         dfs(nr,nc);
      }
   }
}
vector<int>f(vector<int>a,int r,int c){
   mp.clear();
   int n=(a.size()+4)/4;
   for(int i=0;i<n;i++)mp[make_pair(0,i)]=a[i];
   int row=0;
   for(int i=n-1;i<=2*n-2;i++)mp[make_pair(row++,n-1)]=a[i];   
   int col=n-1;
   for(int i=2*n-2;i<=3*n-3;i++)mp[make_pair(n-1,col--)]=a[i];   
   row=n-1;
   for(int i=3*n-3;i<4*n-4;i++)mp[make_pair(row--,0)]=a[i];   
   vis.clear();
   cycle.clear();
   dfs(r,c);
   return cycle;
}
int main(){
   int t,n,v;
   scanf("%d",&t);
   while(t--){
      scanf("%d",&n);
      N=n;
      dir[0][0]=-(n-1), dir[0][1]=-1;
      dir[1][0]=-(n-1), dir[1][1]=1;
      dir[2][0]=+(n-1), dir[2][1]=-1;
      dir[3][0]=+(n-1), dir[3][1]=1;
 
      dir[4][0]=-1, dir[4][1]=-(n-1);
      dir[5][0]=-1, dir[5][1]=+(n-1);
      dir[6][0]=+1, dir[6][1]=-(n-1);
      dir[7][0]=+1, dir[7][1]=+(n-1);
      vector<int>a,b;
      int sa,sb;
      for(int i=0;i<n*4-4;i++){
         scanf("%d",&v);
         a.push_back(v);
         if(v==-1)sa=i%2;
      }
      for(int i=0;i<n*4-4;i++){
         scanf("%d",&v);
         b.push_back(v);
         if(v==-1)sb=i%2;
      }
      bool ok=false;
      if(n%2==0){
         vector<int>eva=f(a,0,0);
         vector<int>oda=f(a,0,1);
         vector<int>evb=f(b,0,0);
         vector<int>odb=f(b,0,1);
         if(sa!=sb)ok=false;
         else{
            if(sa==0){
               ok=(oda==odb && check(eva,evb));
            }
            else{
               ok=(eva==evb && check(oda,odb));
            }
         }
      }
      else{
         vector<int>ca=f(a,0,0);
         vector<int>cb=f(b,0,0);
//         cout<<"ca=";for(int i=0;i<int(ca.size());i++){ cout<<ca[i]<<" "; }cout<<endl;
//         cout<<"cb=";for(int i=0;i<int(ca.size());i++){ cout<<cb[i]<<" "; }cout<<endl;
         ok=check(ca,cb);
      }
      if(ok)puts("YES");
      else puts("NO");
   }
   return 0;
}