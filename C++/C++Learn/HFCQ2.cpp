/*
    AUTHOR:         BHUVNESH JAIN
    INSTITUITION:   BITS PILANI, PILANI
*/
#include <bits/stdc++.h>
 
using namespace std;
 
#define fastio          std::ios_base::sync_with_stdio(false);cin.tie(0);cout.tie(0)
#define PAUSE_EXE       assert(false)
#define inchar          getchar_unlocked
#define outchar(x)      putchar_unlocked(x)
#define LL              long long
#define LD              long double
#define MAX             200005
#define MOD             1000000007LL
#define REP(i,n)        for(__typeof(n) i=0; i<n; ++i)
#define CREP(i,n)       for(__typeof(n) i=n-1; i>=0; --i)
#define MYREP(i,a,b)    for(__typeof(a) i=a; i<=b; ++i)
#define MYCREP(i,a,b)   for(__typeof(a) i=b; i>=a; --i)
#define SET(a, b)       memset(a, b, sizeof(a))
#define sz(a)           int((a).size())
#define pb              push_back
#define mp              make_pair
#define fi              first
#define sec             second
#define all(c)          (c).begin(),(c).end()
#define allr(c)         (c).rbegin(),(c).rend()
#define loop(c,i)       for(typeof(c.begin()) i = c.begin(); i != c.end(); i++)
#define present(c,x)    ((c).find(x) != (c).end())
#define cpresent(c,x)   (find(all(c),x) != (c).end())
 
const double EPS = 1e-10;
 
template <typename T>
void inPos(T &x) {
    register T c = inchar();
    while(((c<48) || (c>57)) && (c!='-')) c = inchar();
    x = 0;
    for(;c<48 || c>57; c = inchar());
    for(;c>47 && c<58; c = inchar())    x=(x<<3)+(x<<1)+(c-48);
}
 
LL mulmod(LL a,LL b, LL m){LL q=(LL)(((LD)a*(LD)b)/(LD)m);LL r=a*b-q*m;if(r>m)r%=m;if(r<0)r+=m;return r;}
template <typename T> T mod(T a, T b) {return (a < b ? a : a % b);}
template <typename T>T expo(T e, T n){T x=1,p=e;while(n){if(n&1)x=x*p;p=p*p;n>>=1;}return x;}
template <typename T>T power(T e, T n, T m){T x=1,p=e;while(n){if(n&1)x=mulmod(x,p,m);p=mulmod(p,p,m);n>>=1;}return x;}
template <typename T> T gcd(T a, T b){if(a%b) return gcd(b,a%b);return b;}
template <typename T> T lcm(T a, T b){return (a*(b/gcd(a,b)));}
 
bool rabin_miller(LL p) {
    if (p<2)                return false;
    if (p!=2 && p%2==0)     return false;
    if (p<8)                return true;
    LL s = p-1, val = p-1, a, m, temp;
    while (s%2==0)
        s/=2;
    for (int i=0; i<10; ++i) {
        a = 1LL*rand()%val + 1LL;
        temp = s;
        m = power(a, temp, p);
        while (temp!=(p-1) && m!=1 && m!=(p-1)) {
            m = mulmod(m, m, p);
            temp<<=1;
        }
        if (m!=(p-1) && temp%2==0)
            return false;
    }
    return true;
} 
 
LL brent(LL n) {
    if (n%2==0)
        return 2;
    LL x, y, c, m, g, r, q, k, ys, w;
    y = 1LL*rand()%(n-1) + 1LL;
    c = 1LL*rand()%(n-1) + 1LL;
    m = 1LL*rand()%(n-1) + 1LL;
    g = r = q = 1LL;
    while (g==1) {
        x = y;
        for (LL i=0; i<r; ++i)
            y = (mulmod(y,y,n) + c)%n;
        k = 0; 
        while (k<r && g==1) {
            ys = y;
            w = min(m, r-k);
            for (int i=0; i<w; ++i) {
                y = (mulmod(y,y,n) + c)%n;
                q = mulmod(q,(abs(x-y))%n,n);
            }
            g = gcd(q, n);
            k += m;
        }
        r=r*2;
    }
    if (g==n) {
        while (true) {
            ys = (mulmod(ys,ys,n) + c)%n;
            g = gcd(abs(x-ys), n);
            if (g>1)
                break;
        }
    }
    return g;
}
  
int main() {
    #ifndef ONLINE_JUDGE
        freopen("inp.txt", "r", stdin);
    #endif
    LL count;
    int t;
    // inPos(t);
    scanf("%d", &t);
    LL n, k, ans, temp;
    while (t--) {
        // inPos(n);
        // inPos(k);
        scanf("%lld %lld", &n, &k);
        if (k==1)
            temp = 1;
        else {
            queue<LL> q1;
            vector<LL> q2;
            q2.clear();
            q1.push(k);
            while (!q1.empty()) {
                LL l = q1.front();
                q1.pop();
                if (rabin_miller(l)) {
                    q2.push_back(l);
                    continue;
                }
                LL d = brent(l);
                if (d==l)
                    q1.push(l);
                else {
                    q1.push(d);
                    q1.push(l/d);
                }
            }
            sort(all(q2));
            ans = 1;
            for (int i=0, j; i<sz(q2); ++i) {
                // printf("%lld^", q2[i]);
                count = 1;
                j = i+1;
                while (q2[i]==q2[j] && j<sz(q2)) {
                    count++; j++;
                }
                i = j-1;
                // printf("%lld ", count);
                // assert(count == 1);
                ans = mulmod(ans, (count + 1), MOD);
            }
            temp = ans;
        }
 
        if (n==1)
            ans = 1;
        else {
            queue<LL> q1;
            vector<LL> q2;
            q2.clear();
            q1.push(n);
            while (!q1.empty()) {
                LL l = q1.front();
                q1.pop();
                if (rabin_miller(l)) {
                    q2.push_back(l);
                    continue;
                }
                LL d = brent(l);
                if (d==l)
                    q1.push(l);
                else {
                    q1.push(d);
                    q1.push(l/d);
                }
            }
            sort(all(q2));
            ans = 1;
            for (int i=0, j; i<sz(q2); ++i) {
                // printf("%lld^", q2[i]);
                count = 1;
                j = i+1;
                while (q2[i]==q2[j] && j<sz(q2)) {
                    count++; j++;
                }
                i = j-1;
                // assert(count == 1);
                // printf("%lld ", count);
                ans = mulmod(ans, mulmod(temp, count, MOD) + 1, MOD);
            }
        }
        // printf("%lld, ", temp);
        assert(ans>=0 && ans<MOD);
        printf("%lld\n", ans);
    }
    // temp = power(2LL, 14LL, MOD) + 1;
    // ans = 1LL;
    // for(int i=1; i<=14; ++i)
    //     ans = mulmod(ans, temp, MOD);
    // printf("%lld\n", ans);
    return 0;
}