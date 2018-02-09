#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <map>
#include <tuple>
#include <fstream>

// Assigning an id to these special types
#define KEYWORD_ID 0
#define LITERAL_ID 1
#define IDENTIFIER_ID 2

using namespace std;

// reads the keywords from the keywords file and inserts into this array
vector<string> keywords;

// A Hash Table for storing the type of each token which is not a keyword
// the first integer is the id to this type. The second string is the string
// to be displayed in the type column of the output file
const map < int, pair< string, vector<char> > > char_token_types = {
  { 3, { "Arithmetic Operator", { '+', '-', '*', '/' } } },
  { 4, { "Relational Operator", { '<', '>' } } },
  { 5, { "Assignment Operator", { '=' } } },
  { 6, { "Special Symbol", { '(', ')', '{', '}', ',', ';' } } }
};

// this array stores the tokens.
// the first int is the token_id, second string is the actual token
// read from input file. The third int is
vector< tuple<int, string, int, int, int> > tokens;
map < string, int > token_id_map;

void populate_keywords(ifstream& keywords_file) {
  string line;
  while (getline(keywords_file, line)) {
    keywords.push_back(line);
  }
}

bool is_keyword(const string& str) {
  if ( find(keywords.begin(), keywords.end(), str) != keywords.end() )
    return true;
  return false;
}

bool is_number(const string& str) {
  if (str == "")
    return false;
  for (const char& c : str) {
    if (c < '0' || c > '9')
      return false;
  }
  return true;
}

void read_input_file(ifstream& input_file) {
  string line, token;
  int lineNo = 0;
  while (getline(input_file, line)) {
    ++lineNo;
    int start = 1;
    token = "";
    for (const auto& token_char : line) {
      bool char_is_ops = false;
      int char_op_type = -1;
      for (const auto& operator_bundle : char_token_types) {
        if (token_char == ' ')
          break;
        if ( find( operator_bundle.second.second.begin(),
                  operator_bundle.second.second.end(),
                  token_char) != operator_bundle.second.second.end() ) {
          char_is_ops = true;
          char_op_type = operator_bundle.first;
          break;
        }
      }
      if (char_is_ops || token_char == ' ') {
        if (token == "") {}
        else if (is_keyword(token)) {
          if (token_id_map.find(token) == token_id_map.end()) {
            token_id_map[token] = token_id_map.size();
          }
          tokens.push_back( make_tuple( token_id_map[token], token, KEYWORD_ID, lineNo, start) );
        }
        else if (is_number(token)) {
          if (token_id_map.find(token) == token_id_map.end()) {
            token_id_map[token] = token_id_map.size();
          }
          tokens.push_back( make_tuple( token_id_map[token], token, LITERAL_ID, lineNo, start) );
        }
        else {
          if (token_id_map.find(token) == token_id_map.end()) {
            token_id_map[token] = token_id_map.size();
          }
          tokens.push_back( make_tuple( token_id_map[token], token, IDENTIFIER_ID, lineNo, start) );
        }
        if (token_char == ' ')
          start += token.length() + 1;
        else
          start += token.length();
        token = "";
        if (char_is_ops) {
          string tmp_token = string({token_char});
          if (token_id_map.find(tmp_token) == token_id_map.end()) {
            token_id_map[tmp_token] = token_id_map.size();
          }
          tokens.push_back( make_tuple( token_id_map[tmp_token], tmp_token, char_op_type, lineNo, start) );
          ++start;
        }
      } else {
        token.push_back(token_char);
      }
    }
  }
}

string getTypeString(int typeId) {
  switch (typeId) {
    case 0: return "Keyword";
    case 1: return "Literal";
    case 2: return "Identifier";
    default: return (*(char_token_types.find(typeId))).second.first;
  }
  return "";
}

void write_output_file(ofstream& fout) {
  fout << "id,value,type,line,char\n";
  for (const auto& t : tokens) {
    fout << get<0>(t) << ",\"" << get<1>(t) << "\"," << getTypeString(get<2>(t)) << "," << get<3>(t) << "," << get<4>(t) << "\n";
  }
}

int main(int argc, char const *argv[]) {
  if (argc < 4) {
    cout << "Invalid arguments\n";
    cout << "usage :: " << argv[0] << " <keywords_file> <file_to_analyse> <output_file_name>\n";
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
  read_input_file(ifile);
  ifile.close();
  ofile.open(argv[3]);
  write_output_file(ofile);
  ofile.close();
  return 0;
}
