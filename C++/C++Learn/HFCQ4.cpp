#include<bits/stdc++.h>
using namespace std;
typedef long long int uli;
const int mx = 1e5+10;
struct suffixArray {
   char *s;
   int n, sa[mx],as[mx],lcp[mx];
   int o[mx],tmp[mx],c[mx];
 
   suffixArray(char* s):s(s){
      n = strlen(s);
      s[n++] = '$';
   }
   void srt(int k){
      memset(c,0,sizeof c);
      for(int i=0;i<n;i++){
         c[i+k<n?o[i+k]:0]++;
      }
      int sm = 0;
      int maxi = max(300,n);
      for(int i=0;i<maxi;i++){
         int v = c[i];
         c[i] = sm;
         sm+=v;
      }
 
      for(int i=0;i<n;i++){
         int idx = sa[i]+k<n?o[sa[i]+k]:0;
         tmp[c[idx]++] = sa[i];
      }
      for(int i=0;i<n;i++) 
         sa[i] = tmp[i];
   }
   void csa(){ 
      for(int i=0;i<n;i++){
         o[i] = s[i];
         sa[i] = i;
      }
      for(int k=1;k<n;k<<=1){
         srt(k);
         srt(0);
         tmp[sa[0]] = 0;
         int idx = 0;
         for(int i=1;i<n;i++){
            int o1 = 0, o2 = 0; 
            if(sa[i]+k<n) o1 = o[sa[i]+k];
            if(sa[i-1]+k<n) o2 = o[sa[i-1]+k];
 
            if(o[sa[i]]!=o[sa[i-1]] || o1!=o2){
               idx++;
            }
            tmp[sa[i]] = idx;
         }
         for(int i=0;i<n;i++){
            o[i] = tmp[i];
         }
      }
   }
   void clcp(){
      for(int i=0;i<n;i++)
         as[sa[i]] = i;
      int l = 0;
      for(int i=0;i<n;i++){
         l = max(0,l-1);
         if(as[i]==0) l = 0;
         else while(s[i+l]==s[sa[as[i]-1]+l]){
            l++;
         }
         tmp[i] = l;
      }
      for(int i=0;i<n;i++)
         lcp[i] = tmp[sa[i]];
   }
};
 
char a[mx],b[mx],ab[mx];
int fa[mx],fb[mx],fab[mx];
int ft[mx];
void upd(int i,int v){
   i=mx-i-3;
   for(++i;i<mx;i+=(i&-i))ft[i]+=v;
}
int qry(int i){
   i=mx-i-3;
   int a=0;
   for(++i;i>0;i-=(i&-i))a+=ft[i];
   return a;
}
void solve(char s[],int f[]){
   int n=strlen(s);
   suffixArray sa(s);
   sa.csa();
   sa.clcp();
   /*
      cout<<"s="<<s<<endl;
      cout<<" sa=";for(int i=0;i<=n;i++)cout<<sa.sa[i]<<" ";cout<<endl;
      cout<<"lcp=";for(int i=0;i<=n;i++)cout<<sa.lcp[i]<<" ";cout<<endl;
      */
   vector<pair<int,int> >lcpi;
   for(int i=1;i<=n;i++)lcpi.push_back(make_pair(sa.lcp[i],sa.sa[i]));
   sort(lcpi.begin(),lcpi.end());
   for(int i=0;i<mx;i++)ft[i]=0;
 
   int i=0;
   for(int k=1;k<=n;k++){
      while(i<int(lcpi.size()) && lcpi[i].first<k){
         upd(lcpi[i].second,1);
         i++;
      }
      int q=qry(n-k+1);
      f[k]=i-q;
     //       cout<<"f"<<k<<"="<<f[k]<<endl;
   }
}
int main(){
   scanf("%s %s",a,b);
   int la=strlen(a);
   int lb=strlen(b);
   for(int i=0;i<la;i++)ab[i]=a[i];
   ab[la]='.';
   for(int i=0;i<lb;i++)ab[la+i+1]=b[i];
   ab[la+lb+1]='\0';
   solve(a,fa);   
   solve(b,fb);
   solve(ab,fab);
   int len=la+lb+1;
   for(int k=1;k<=len;k++){
      int r=min(la,len-k);
      int l=max(la-k+1,0);
      if(l<=r){
         fab[k]-=r-l+1;
      }
      //      cout<<"fab "<<k<<"="<<fab[k]<<endl;
   }
   int q;
   scanf("%d",&q);
   while(q--){
      int op,k;
      scanf("%d %d",&op,&k);
      int ans;
      int kab=fa[k]+fb[k]-fab[k];
      if(op==1) ans=kab;
      else if(op==2)ans=fa[k]-kab;
      else if(op==3)ans=fb[k]-kab;
      else if(op==4)ans=fab[k]-kab;
      printf("%d\n",ans);
   }
   return 0;
}