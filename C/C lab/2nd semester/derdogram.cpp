#include <iostream>
#include <vector>
#include <array>
#include <algorithm>
#include <cmath>

using namespace std;

struct coordinates {
	int x,y;
};

vector<coordinates> inp = { {0,0} , {1,1} , {3,1} , {2,4} , {6,3} , {6,6} , {5,2} , {3,5} };
vector<int> pq = {0,1,2,3,4,5,6,7,8};

double adjacency_matrix[8][8];

double dist (coordinates &c1, coordinates &c2) {
	return sqrt(pow(c1.x - c2.x,2) + pow(c1.y - c2.y,2));
}

void populate_matrix () {
	for(int i=0; i<inp.size(); ++i) {
		for(int j=0; j<inp.size(); ++j) {
			adjacency_matrix[i][j] = dist(inp[i],inp[j]);
		}
	}
}

int find_minimum (int n) {
	pq = {0,1,2,3,4,5,6,7};
	pq.erase(pq.begin()+n);
	make_heap(pq.begin(), pq.end(), [&](int n1, int n2) {
		return adjacency_matrix[n][n2] < adjacency_matrix[n][n1];
	});
	return pq.front();
}

int main() {
	populate_matrix();
	for (int i=0; i<inp.size(); ++i) {
		for (int j=0; j<inp.size(); ++j)
			cout<<adjacency_matrix[i][j]<<"\t";
		cout<<endl;
	}
	cout<<endl<<endl;
	for(int i=0; i<inp.size(); ++i) {
		cout<<adjacency_matrix[i][find_minimum(i)]<<"\t"<<find_minimum(i)<<endl;
	}
	return 0;
}