#include <iostream>
#include <vector>

using namespace std;

int main() {
	int T;
	cin>>T;
	vector<int> results(T);
	for(int i=0; i<T; ++i) {
		int rows,columns,elements;
		cin>>rows>>columns>>elements;
		vector<int> row(rows+1,1);
		vector<int> col(columns+1,1);
		int temp;
		for(int j=0; j<elements; ++j) {
			cin>>temp;
			row[temp-1] = 0;
			cin>>temp;
			col[temp-1] = 0;
		}
		row[rows] = 0;
		col[columns] = 0;
		int max_val=0, val=0;
		for(int j=0,prev_index=0; j<=rows; ++j) {
			if(!row[j]) {
				temp = j - prev_index;
				if(temp>max_val)
					max_val=temp;
				prev_index = j+1;
			}
		}
		val = max_val;
		max_val = 0;
		for(int j=0,prev_index=0; j<=columns; ++j) {
			if(!col[j]) {
				temp = j - prev_index;
				if(temp>max_val)
					max_val=temp;
				prev_index = j+1;
			}
		}
		val *= max_val;
		results[i] = val;
	}
	for(int i=0; i<T; ++i)
		cout<<results[i]<<endl;
	return 0;
}