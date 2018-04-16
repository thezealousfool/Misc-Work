#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <vector>
#include <string>
#include <map>
#include <set>
#include <stack>
using namespace std;

/* THERE WILL BE A HEADER CORRESPONDINIG TO THIS
ALSO ANOTHER HEADER FOR REGEX WHICH WILL BE INCLUDED HERE (NOT TOO SURE)
*/

class make_fa
{
	std::map<int, std::string> nfa_map;
	std::map<std::string, int> terminals;
	std::map<char, std::pair<int, int> > priority;
	std::map<std::pair <int, int>, std::vector<int> > transition_table;
 	std::string regex;
	std::string delims;
	int start_state, end_state;

	void set_priority_map();
	std::vector<std::string> postfix(std::vector<std::string>&);

	public:
	explicit make_fa(std::string reg_expression):regex{reg_expression} {delims = "*%|()$";}; // constructor
	void display_transitions();
	std::vector<std::string> tokenize(std::string& delims);
	void make_table();
	std::map<std::pair<int,int>, std::vector<int> > get_transition_table();
	int get_start_state();
	int get_final_state();
	std::map<std::string, int> get_terminals();
};
/* doing this just to avoid using many library functions
	REMOVE THIS COMMENT BEFORE SUBMITTING
*/
void make_fa::set_priority_map()
{
	priority['|'] = std::pair<int,int>(1,1);
	priority['%'] = std::pair<int,int>(2,2);
	priority['*'] = std::pair<int,int>(3,3);
	priority['('] = std::pair<int,int>(0,5);
	priority[')'] = std::pair<int,int>(4,4);
	priority['$'] = std::pair<int,int>(0,0);
}
std::vector<std::string> make_fa::postfix(std::vector<std::string>& ip_vector)
{
	std::vector<std::string> post_vector;
	std::stack<char> post_stack;
	post_stack.push('(');
	set_priority_map();
	for (std::string elem : ip_vector)
	{
		if (terminals.find(elem) != terminals.end()) // is a terminal
			post_vector.push_back(elem);
		else if (elem[0] == ')' || elem[0] == '$')
		{
			
			while (post_stack.top() != '(')
			{
				post_vector.push_back(std::string(1,post_stack.top()));
				//std::cout << "Popping" << post_stack.top() << endl;
				post_stack.pop();
				//std::cout << "Popped" << endl;	
			}
			post_stack.pop();
		}
		else // is an operator or bracket or eos
		{
			char top_elem = post_stack.top();
			while (priority[top_elem].first >= priority[elem[0]].second)
			{
				post_vector.push_back(std::string(1,post_stack.top()));
				//std::cout << "Popping" << post_stack.top() << endl;
				post_stack.pop();
				//std::cout << "Popped" << endl;
				top_elem = post_stack.top();
			}
			//std::cout << "lol" << endl;
			post_stack.push(elem[0]);
		}
	}
	return post_vector;
}
//void make_fa::add_states(std::pair<int,int>& nfa1, std::pair<int,int>& nfa2, char& op, int& state_no)
//{

//}
std::vector<std::string> make_fa::tokenize(std::string& delims)
{
	std::size_t pos=0, cur, len=regex.length();
	std::vector<std::string> tokens;
	terminals["#"] = 0;
	int term_no = 1;
	for (cur = 0; cur < regex.length(); cur++)
	{
		if (delims.find(regex.at(cur)) != std::string::npos)
		{
			if (cur>pos)
			{
				tokens.push_back(regex.substr(pos, cur-pos)); // assuming optimization
				if (terminals.find(regex.substr(pos,cur-pos)) == terminals.end()) terminals[regex.substr(pos, cur-pos)] = term_no++; 
			}
			tokens.push_back(std::string(1,regex.at(cur)));
			pos = cur+1;
		}
	}
	return tokens;
}
void make_fa::make_table()
{
	std::vector<std::string> tokens = tokenize(delims);
	for (std::string& token : tokens) std::cout << token << endl; // test tokens
	std::cout << "Terminals: " << endl;
	for (std::map<std::string,int>::iterator it=terminals.begin(); it!=terminals.end(); ++it) std::cout << it->first << " => " << it->second << '\n';

	/* convert to postfix
	*/

	std::vector<std::string> post = postfix(tokens);
	std::cout << "Postfix: " << endl;
	for (std::string& token : post) std::cout << token;
	std::cout << endl;
	/*make the nfa*/

	std::stack<std::pair<int, int> > post_processor; // holds start and end state nos
	int cur_first = 0, cur_end = 0, state_no = 0;
	for (std::string& token : post)
	{
		if (terminals.find(token) != terminals.end()) // is a terminal
		{
			int start = state_no++, end = state_no++;
			post_processor.push(std::pair<int,int>(start,end));
			transition_table[std::pair<int,int>(start, (terminals[token]))].push_back(end); // d(start,terminal_no) = end
		}
		else // make the nfa based on op
		{
			if (token[0] == '|') // OR operaton
			{
				int start = state_no++, end = state_no++;
				std::pair<int,int> nfa2 = post_processor.top();
				post_processor.pop();
				std::pair<int,int> nfa1 = post_processor.top();
				post_processor.pop();
				transition_table[std::pair<int,int>(start, 0)].push_back(nfa1.first);
				transition_table[std::pair<int,int>(start, 0)].push_back(nfa2.first);
				transition_table[std::pair<int,int>(nfa1.second, 0)].push_back(end);
				transition_table[std::pair<int,int>(nfa2.second, 0)].push_back(end);
				post_processor.push(std::pair<int,int>(start, end));
			}
			if (token[0] == '%') // CONCAT operaton
			{
				//int start = state_no++, end = state_no++;
				std::pair<int,int> nfa2 = post_processor.top();
				post_processor.pop();
				std::pair<int,int> nfa1 = post_processor.top();
				post_processor.pop();
				transition_table[std::pair<int,int>(nfa1.second, 0)].push_back(nfa2.first);
				post_processor.push(std::pair<int,int>(nfa1.first, nfa2.second));
			}
			if (token[0] == '*') // KLEENE CLOSURE operaton
			{
				int start = state_no++, end = state_no++;
				std::pair<int,int> nfa = post_processor.top();
				post_processor.pop();
				transition_table[std::pair<int,int>(start, 0)].push_back(nfa.first);
				transition_table[std::pair<int,int>(nfa.second, 0)].push_back(end);
				transition_table[std::pair<int,int>(start, 0)].push_back(end);
				transition_table[std::pair<int,int>(nfa.second, 0)].push_back(nfa.first);
				post_processor.push(std::pair<int,int>(start, end));
			}
		}

	}
	start_state = post_processor.top().first;
	end_state = post_processor.top().second;
	
	
	/* THIS GENERATED NFA MAY NEDD COMPRESSION/OPTIMIZATION */

}
void make_fa::display_transitions()
{
	std::cout << "e-NFA Transitions: " << endl;
	std::cout << "---------------------------------------------------------" << endl;
	for (std::map<std::pair<int,int>,std::vector<int> >::iterator it=transition_table.begin(); it!=transition_table.end(); ++it) 
	{	std::cout << "d(" << it->first.first << "," << it->first.second <<  ") => [ ";
		for (int& ele : it->second) std::cout << ele << " ";
		std::cout << "]" << endl;
	}
	std::cout << "Start State: " << start_state << " End State: " << end_state << endl;
}
std::map<std::pair<int,int>, std::vector<int> > make_fa::get_transition_table()
{return transition_table;}
int make_fa::get_start_state()
{return start_state;}
int make_fa::get_final_state()
{return end_state;}
std::map<std::string, int> make_fa::get_terminals()
{return terminals;}
/*
int main(int argc, char const *argv[])
{
	std::cout << "Input format: " << endl;
	std::cout << "| - OR, . - CONCAT, * - KLEENE" << endl;
	std::cout << "E.g: (a|b)*.c*" << endl;
	std::string regex;
	std::getline(std::cin, regex); // get the regex from console
	make_fa mf(regex);
	mf.make_table();
	mf.display_transitions();
	return 0;
};
*/