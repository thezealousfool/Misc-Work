#include <iostream>
#include <vector>
using namespace std;
int main() {
    int n,k;
    bool b = true;
    cin>>n;
    vector<int> v(n);
    for (int i = 0; i<n; ++i) {
        cin>>v[i];
    }
    for(int j = 1; j<n; ++j) {
        int tmp = v[j];
        for (int i = 0; i<j; ++i){
            if (v[i]>tmp){
                for(int k = j; k>= i; k++){
                    v[k]=v[k-1];
                }
                v[i-1]=tmp;
            }
        }
        for (int i = 0; i<v.size(); ++i)
            cout<<v[i]<<" ";
        cout<<endl;
    }
    return 0;
}
