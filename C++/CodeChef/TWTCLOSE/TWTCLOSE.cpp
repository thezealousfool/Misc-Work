/*input
3 6
CLICK 1
CLICK 2
CLICK 3
CLICK 2
CLOSEALL
CLICK 1
*/

#include <bits/stdc++.h>
using namespace std;

bool tweets[1001];

int main() {
	int N, K;
	cin>>N>>K;
	string command;
	for(int i=0; i<N; ++i)
		tweets[i] = false;
	int count = 0;
	while(K--) {
		cin>>command;
		if (command == "CLOSEALL") {
			for (int i=0; i<N; ++i)
				tweets[i] = false;
			count = 0;
		}
		else if (command == "CLICK") {
			int tweet_no;
			cin>>tweet_no;
			if (tweets[tweet_no-1]) {
				tweets[tweet_no-1] = false;
				--count;
			}
			else {
				tweets[tweet_no-1] = true;
				++count;
			}
		}
		cout<<count<<endl;
	}
	return 0;
}