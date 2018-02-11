#include <iostream>
#include <iomanip>
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
#define INVALID_IDENTIFIER_ID 99

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
// the first parameter (int) is the token_id, second parameter
// (string) is the actual token read from input file. The
// third parameter (int) is a number representing the type
// of the token, and the last two parameters (int) represent
// the line number and character number in the line (position)
vector< tuple<int, string, int, int, int> > tokens;

// this hash table is used to assign unique token_id to every
// new token and reuse the old token_id for tokens which have
// already been assigned an id.
map < string, int > token_id_map;


// this function reads the words from the supplied keywords file
// and creates the keywords array from it.
void populate_keywords(ifstream& keywords_file) {
  string line;
  while (getline(keywords_file, line)) {
    keywords.push_back(line);
  }
}

// takes a string and checks if it is a keyword or not
bool is_keyword(const string& str) {
  if ( find(keywords.begin(), keywords.end(), str) != keywords.end() )
    return true;
  return false;
}

// takes a string and checks if it is a literal or not
// it checks for numbers or character constants like 'a'
bool is_literal(const string& str) {
  if (str[0] == '\'' && str[str.length()-1] == '\'') {
    if (str.length() == 3)
      return true;
    return false;
  }
  if (str[0] == '\"' && str[str.length()-1] == '\"') {
    return true;
  }
  for (const char& c : str) {
    if (c < '0' || c > '9')
      return false;
  }
  return true;
}

// takes a string and checks if it marks the begining of a single line comment
bool is_singleline_comment(const string& str) {
  if (str[0] == '/' && str[1] == '/')
    return true;
  return false;
}

// takes a string and checks if it marks the begining of a multi line comment
bool is_multiline_comment_start(const string& str) {
  if (str[0] == '/' && str[1] == '*')
    return true;
  return false;
}

// takes a string and checks if it marks the end of a multi line comment
bool is_multiline_comment_end(const string& str) {
  if (str[str.length()-2] == '*' && str[str.length()-1] == '/')
    return true;
  return false;
}

// this function is the main parser function.
// It reads the input_file (file_to_analyse) line by line
// tokenises it by checking for space or any of the
// operators, and finally inserts them into the tokens array
// with additional collected information like type of toke,
// position of token and token id.
void parse_input_file(ifstream& input_file) {
  string line, token;
  int lineNo = 0;
  // boolean to store if multiline comment in progress
  bool multiline_comment = false;
  // read line wise
  while (getline(input_file, line)) {
    // keep track of line number
    ++lineNo;
    // keep track of the character number in the line
    int start = 1;
    token = "";
    // boolean to store if singleline comment in progress
    bool singleline_comment = false;
    // iterate over the characters in the line
    for ( int loop_ind = 0; loop_ind < line.length(); ++loop_ind ) {
      const char token_char = line[loop_ind];
      const char next_token_char =
      loop_ind == line.length()-1 ? '\n' : line[loop_ind + 1];
      const char prev_token_char =
      loop_ind == 0 ? '\n' : line[loop_ind - 1];
      bool char_is_ops = false;
      int char_op_type = -1;
      // check if it is a space or an character operator
      for (const auto& operator_bundle : char_token_types) {
        if (token_char == ' ')
          break;
        if (token_char == '/' &&
            (next_token_char == '/' || next_token_char == '*'
              || prev_token_char == '/' || prev_token_char == '*'))
          break;
        if (token_char == '*' && (next_token_char == '/' || prev_token_char == '/'))
          break;
        if ( find( operator_bundle.second.second.begin(),
                  operator_bundle.second.second.end(),
                  token_char) != operator_bundle.second.second.end() ) {
          char_is_ops = true;
          char_op_type = operator_bundle.first;
          break;
        }
      }
      // if character encountered is indeed a space of a
      // character operator, then we process the token
      // string generated so far
      if (char_is_ops || token_char == ' ') {
        if (token == "" || singleline_comment) {}
        else if (multiline_comment) {
          if (is_multiline_comment_end(token)) {
            multiline_comment = false;
          }
        }
        // we check the type of token and process it
        else if (is_keyword(token)) {
          if (token_id_map.find(token) == token_id_map.end()) {
            token_id_map[token] = token_id_map.size();
          }
          tokens.push_back( make_tuple(
            token_id_map[token], token, KEYWORD_ID, lineNo, start
          ));
        }
        else if (is_literal(token)) {
          if (token_id_map.find(token) == token_id_map.end()) {
            token_id_map[token] = token_id_map.size();
          }
          tokens.push_back( make_tuple(
            token_id_map[token], token, LITERAL_ID, lineNo, start
          ));
        }
        else if (is_singleline_comment(token)) {
          singleline_comment = true;
        }
        else if (is_multiline_comment_start(token)) {
          multiline_comment = true;
        }
        else {
          if (token_id_map.find(token) == token_id_map.end()) {
            token_id_map[token] = token_id_map.size();
          }
          if ((token[0] >= 'a' && token[0] <= 'z')
            || (token[0] >= 'A' && token[0] <= 'Z')
            || token[0] == '_' )
            tokens.push_back( make_tuple(
              token_id_map[token], token, IDENTIFIER_ID, lineNo, start
            ));
          else
            tokens.push_back( make_tuple(
              token_id_map[token], token, INVALID_IDENTIFIER_ID, lineNo, start
            ));
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
          tokens.push_back( make_tuple(
            token_id_map[tmp_token], tmp_token, char_op_type, lineNo, start
          ));
          ++start;
        }
      }
      // if not space nor character operator then we append
      // the character to the token string generated so far
      else {
        token.push_back(token_char);
      }
    }
    if (token != "" && !singleline_comment) {
      if (multiline_comment) {
        if (is_multiline_comment_end(token)) {
          multiline_comment = false;
        }
      }
      else if (is_keyword(token)) {
        if (token_id_map.find(token) == token_id_map.end()) {
          token_id_map[token] = token_id_map.size();
        }
        tokens.push_back( make_tuple(
          token_id_map[token], token, KEYWORD_ID, lineNo, start
        ));
      }
      else if (is_literal(token)) {
        if (token_id_map.find(token) == token_id_map.end()) {
          token_id_map[token] = token_id_map.size();
        }
        tokens.push_back( make_tuple(
          token_id_map[token], token, LITERAL_ID, lineNo, start
        ));
      }
      else {
        if (token_id_map.find(token) == token_id_map.end()) {
          token_id_map[token] = token_id_map.size();
        }
        if ((token[0] >= 'a' && token[0] <= 'z')
          || (token[0] >= 'A' && token[0] <= 'Z')
          || token[0] == '_' )
          tokens.push_back( make_tuple(
            token_id_map[token], token, IDENTIFIER_ID, lineNo, start
          ));
        else
          tokens.push_back( make_tuple(
            token_id_map[token], token, INVALID_IDENTIFIER_ID, lineNo, start
          ));
      }
    }
  }
}

// this function returns the string that is displayed in the output file
// based on the token type number.
string getTypeString(int typeId) {
  switch (typeId) {
    case 0: return "Keyword";
    case 1: return "Literal";
    case 2: return "Identifier";
    case 99: return "Invalid Identifier";
    default: return (*(char_token_types.find(typeId))).second.first;
  }
  return "";
}

// this function creates and writes to the output token file by iterating over
// the tokens array generated by the parser (the parse_input_file function)
void write_output_file(ofstream& fout) {
  fout << setw(10) << "id"
        << setw(20) << "value"
        << setw(25) << "type"
        << setw(10) << "line"
        << setw(10) << "char"
        << '\n';
  for (int i = 0; i < 75; i++)
    fout << '-';
  fout << '\n';
  for (const auto& t : tokens) {
    fout << setw(10) << get<0>(t)
          << setw(20) << get<1>(t)
          << setw(25) << getTypeString(get<2>(t))
          << setw(10) << get<3>(t)
          << setw(10) << get<4>(t) << "\n";
  }
}

// the main driver function
int main(int argc, char const *argv[]) {
  if (argc < 4) {
    cout << "Invalid arguments\n";
    cout << "usage :: " << argv[0]
          << " <keywords_file> <file_to_analyse> <output_file_name>\n";
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
  ofile.open(argv[3]);
  write_output_file(ofile);
  ofile.close();
  cout << "Successfully written to " << argv[3] << "\n";
  return 0;
}
