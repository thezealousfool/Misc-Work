#include <iostream>
#include <vector>
#define max 100

using namespace std;
typedef long long int Int;
const Int Mod = (Int)1E9 + 7;

Int dp[234][123][123][4];

Int compute(int B, int N, int R, int D) {
    if(R<=0) {
        return 1;
    }
    if(B==0) {
        return 0;
    }
    Int &val = dp[B][N][R][D];
    if(val!=-1) {
    	return val;
    }

    val = 0;
    if(B!=0) {
    	if(D!=2) {
    		val += compute(B-1,N,R,D+1);
    		val %= Mod;
    	}
    	val += compute(B-1,N,R-6,D);
    	val %= Mod;
    	val += compute(B-1,N,R-4,D);
    	val %= Mod;
    	val += compute(B-1,N,R-2,D);
    	val %= Mod;
    	val += compute(B-1,N,R-1,D);
    	val %= Mod;
    }
    if(N!=0) {
    	val += compute(B,N-1,R,D);
    	val %= Mod;
    	val += compute(B,N-1,R-6,D);
    	val %= Mod;
    	val += compute(B,N-1,R-4,D);
    	val %= Mod;
    	val += compute(B,N-1,R-2,D);
    	val %= Mod;
    	val += compute(B,N-1,R-1,D);
    	val %= Mod;
    }
    return val;
}

int main() {
	int T;
	cin>>T;
	for(int i=0; i<234; ++i) {
		for(int j=0; j<123; ++j) {
			for(int k=0; k<123; ++k) {
				for (int l=0; l<4; ++l)
					dp[i][j][k][l] = -1;
			}
		}
	}
	while(T--) {
		int B,N;
		cin>>B>>N;
		if(max/(B+N) > 6) {
			cout<<0;
			continue;
		}
		Int val = compute(B,N,max,0);
		cout<<val<<endl;
	}
	return 0;
}