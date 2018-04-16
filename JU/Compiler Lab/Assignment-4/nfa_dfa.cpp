#include <iostream>
#include <map>
#include <vector>
#include <set>
#include <string>
#include <queue>
#include <algorithm>
#include "make_nfa.cpp"
#include "lexical_analyser.cpp"
using namespace std;

class fa{
	string sym;
	//vector<string> state;
	int start, end;
	vector<int> terms;
	map<pair<int, int>, vector<int> > trans;
	map<pair<vector<int>,int>, vector<int> > dfa;
	vector<int> start_state;
	vector<vector<int> > end_state;
	map<string, int> terminal_map;
	public:
		/*fa(fa &x){
			sym = x.sym;
			state = x.state;
			m = x.m;
			start_state = x.start_state;
			final = x.final;
		}*/
	fa(map<pair<int, int>, vector<int> > trs, map<string, int> t, int s, int e){
		trans = trs;
		terminal_map = t;
		start = s;
		end = e;
		//terms.push_back(0);
		for (map<string,int>::iterator it=t.begin(); it!=t.end(); ++it)
		{
			if(it->second!=0)
			terms.push_back(it->second);
		}
	}
		
	vector<int> e_closure(int state){
		queue<int> q;
		vector<int> vec;
		// /vector<int> mark(st.size());
		/*
		for(char ch:str){
			string x="";
			x = x+ch;
			if(find(vec.begin(),vec.end(),x) == vec.end()){
				vec.push_back(x);
				q.push(x);
			}
		}
		*/
		//q.push(state);
		vec.push_back(state);
		for (int& s : trans[pair<int,int>(state, 0)]){
			q.push(s);
			vec.push_back(s);
		}
		
		while(!q.empty()){
			int s = q.front();
			q.pop();
			for(int& x: trans[pair<int,int>(s, 0)]){
				if(find(vec.begin(),vec.end(),x) == vec.end()){
					vec.push_back(x);
					q.push(x);
				}
			}
		}

		return vec;

	}

	bool match(const string& token_str) {
		vector<int> current_state = start_state;
		for (const char token_char : token_str) {
			string token = string(1, token_char);
			if (terminal_map.find(token) != terminal_map.end()) {
				int token_id = terminal_map[token];
				// find < current_state, token_id > in dfa (map)
				auto new_state_it = dfa.find(make_pair(current_state, token_id));
				if (new_state_it != dfa.end()) {
					current_state = (new_state_it->second);
				} else {
					return false;
				}
			} else {
				return false;
			}
		}
		if (find(end_state.begin(), end_state.end(), current_state) != end_state.end()) {
			return true;
		}
		return false;
	}

	void print(){
		cout << "DFA Transitions: " << endl;
		cout << "---------------------------------------------------------" << endl;
		for (map<pair<vector<int>,int>,vector<int> >::iterator it=dfa.begin(); it!=dfa.end(); ++it) {
			cout << "d([ ";
			for (int i : it->first.first) cout << i << " ";
			cout << "]," << it->first.second <<  ") => [ ";
			for (int& ele : it->second) cout << ele << " ";
			cout << "]" << endl;
		}
		cout << "Start State: " << endl;
		cout << "[ ";
		for (int i : start_state) cout << i << " ";
		cout << "]" << endl;
		cout << "End State: " << endl;
		for (vector<int> i : end_state){ 
			cout << "[ ";
			for (int j : i) cout << j << " ";
			cout << "]" << endl;
		}
	}
	
	void convert_to_dfa()
	{
		//start is 2;
		start_state = e_closure(start);
		//dfa[pair<vector<int>, int>(start, 0)] = start;
		set<vector<int> > states;

		//states.insert(start);
		set<vector<int> > marked;
		
		sort(start_state.begin(), start_state.end());
		vector<int> t = start_state;
		states.insert(t);
		while(true){
		
			bool flag=true;
			marked.insert(t);
			//cout << "t:" << endl;
			//for (int& i : t) cout << i << " ";
			for (int& i : terms) {
				set<int> new_s;
				for (int& j : t) {
					vector<int> p = trans[pair<int,int>(j, i)];
					for (int q : p) for (int r : e_closure(q)) new_s.insert(r);
				}
				vector<int> t2;
				for (int j : new_s) t2.push_back(j);
				sort(t2.begin(), t2.end());

				dfa[pair<vector<int>,int>(t, i)] = t2;
				if (states.find(t2) == states.end()) states.insert(t2);
				
				//cout << "New:";
				//for (int x : new_s) cout << x << " ";
				//cout << endl;
			}
			for (vector<int> vec : states){
				if (marked.find(vec) == marked.end()){
					t=vec;
					flag=false;
					break;
				}
			}
			if (flag) break;
		}
		for (vector<int> vec : states)
		{
			if (find(vec.begin(), vec.end(), end) != vec.end()) end_state.push_back(vec);
		}

	}
	void print_dfa()
	{
		cout << "Transitions: " << endl;
		for (map<pair<vector<int>,int>,vector<int> >::iterator it=dfa.begin(); it!=dfa.end(); ++it) 
		{	cout << "d(";
			for (int i : it->first.first) cout << i;
			cout << "," << it->first.second <<  ") => [ ";
			for (int& ele : it->second) cout << ele << " ";
			cout << "]" << endl;
		}
	}

	
};
int main(int argc, char const *argv[]) {
  /* Tokenizing */
	if (argc < 4) {
    cout << "Invalid arguments\n";
    cout << "usage :: " << argv[0]
          << " <keywords_file> <file_to_analyse> <regex_file>\n";
    return -1;
  }
  ifstream ifile;
  ofstream ofile;
  ifile.open(argv[1]);
  if (!ifile) {
    cout << "Error opening keywords file. Aborting!\n";
    return -1;
  }
  populate_keywords(ifile);
  ifile.close();
  ifile.open(argv[2]);
  if (!ifile) {
    cout << "Error opening input file to analyse. Aborting!\n";
    return -1;
  }
  parse_input_file(ifile);
  ifile.close();
	/* Tokenizing end */
	ifile.open(argv[3]);
	if (!ifile) {
    cout << "Error opening regex file to analyse. Aborting!\n";
    return -1;
  }
	vector<fa> fa_objects;
	string regex;
	while (getline(ifile, regex)) {
		map<pair<int, int>, vector<int>> table;
		make_fa mf(regex);
		mf.make_table();
		table = mf.get_transition_table();
		int start = mf.get_start_state();
		int end = mf.get_final_state();
		map<string, int> terms = mf.get_terminals();

		fa x(table, terms, start, end);
		x.convert_to_dfa();
		x.print();
		fa_objects.push_back(x);
	}
	cout << "\n\nAccepted Tokens:\n";
	for (const auto& t : tokens) {
		string token_value = get<1>(t);
		// cout << token_value << " :: " << x.match(token_value) << "\n";
		bool passed = false;
		if (is_keyword(token_value)) {
			continue;
		}
		for (fa x : fa_objects) {
			if (x.match(token_value)) {
				passed = true;
				break;
			}
		}
		if (passed) {
			cout << token_value << "\n";
		}
	}
	return 0;
}