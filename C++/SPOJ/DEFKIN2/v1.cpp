#include <iostream>
#include <deque>
#include <vector>

using namespace std;

typedef long long int Int;

int main() {
	Int T;
	cin>>T;
	vector<int> answer(T);
	for(Int i=0; i<T; ++i) {
		Int rows,columns,elements;
		cin>>rows>>columns>>elements;
		deque<Int> row_max;
		deque<Int> column_max;
		Int max = rows*columns;
		row_max.push_back(rows);
		column_max.push_back(columns);
		while(elements--) {
			Int r = row_max.front();
			row_max.pop_front();
			Int c = column_max.front();
			column_max.pop_front();
			row_max.push_back(r/2);
			row_max.push_back((r-1)/2);
			column_max.push_back(c/2);
			column_max.push_back((c-1)/2);
		}
		answer[i] = row_max.front()*column_max.front();
	}
	for(Int i=0; i<T; ++i)
		cout<<answer[i]<<endl;
	return 0;
}