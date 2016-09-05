/*input
*/

#include <bits/stdc++.h>
#define max 8
using namespace std;

bool is_safe (int &x, int &y) {
	return (x<max && y<max && x>=0 && y>=0);
}

void print_solution(vector<pair<int,int>> &path) {
	for(auto pos = path.begin(); pos!=path.end(); ++pos)
		cout<<"("<<(*pos).first<<","<<(*pos).second<<")->";
	cout<<"End"<<endl;
}

bool solve_knight_tour()

int main() {
	vector<pair<int,int>> path;
	path.push_back(make_pair(2,3));
	print_solution(path);
	return 0;
}