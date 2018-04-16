KEYWORD     "if"|"else"|"for"|"int"|"float"|"void"|"return"|"char"
ASSOP       =
ROPS        [<>!]=?|==
AOPS        [+\-*/]
SLIT        \"[^"]*\"
CLIT        \'[^']\'
INTLIT      [0-9]+
HEXLIT      0[xX][a-fA-F0-9]+
DECLIT      [0-9]*\.[0-9]*([Ee][+-]?[0-9]+)?
IDEN        [_a-zA-Z]+[_a-zA-Z0-9]*
PUNC        [;,(){}]
MLCOM       \/\*[^\*\/]*\*\/
SLCOM       \/\/[^\n]*
NEWLINE     [\n]
WHITESPACE  [\t ]


%{
#include <stdio.h>

#define     MAPLEN      10000
#define     MAXTOKENLEN 50

typedef struct {
    char    literals[MAPLEN][MAXTOKENLEN];
    int     len;
} map;

map idmap;
map* m = &idmap;
int charPos, linePos;

int find(map* m, char key[]) {
    const int len = m->len;
    int i;
    for (i = 0; i < len; ++i) {
        if (strcmp(m->literals[i], key) == 0 )
            return i;
    }
    return -1;
}

void _unsafe_insert(map* m, char key[]) {
    strcpy(m->literals[m->len], key);
    ++(m->len);
}

int insert(map* m, char key[]) {
    int index;
    if (m->len == MAPLEN)
        return -2;
    index = find(m, key);
    if (index < 0) {
        _unsafe_insert(m, key);
        return (m->len - 1);
    }
    return index;
}

void _printformat(char id[], char lexeme[], char type[], char pos[]) {
    printf("%5s\t%40s\t%20s\t%15s\n", id, lexeme, type, pos);
}

void printformat(char id[], char lexeme[], char type[]) {
    char* pos = malloc(15);
    sprintf(pos, "(%d, %d)", linePos, charPos);
    _printformat(id, lexeme, type, pos);
    free(pos);
}

void multiline(char text[]) {
    int len, i;
    len = strlen(text);
    for(i = 0; i < len; ++i) {
        if (text[i] == '\n')
            ++linePos;
    }
}

void assignId(map* m, char iden[], char* str) {
    int status;
    status = insert(m, iden);
    if (status < 0) {
        sprintf(str, "%s", "Error");
    } else {
        sprintf(str, "%d", status);
    }
}

%}

%%
{MLCOM}         { multiline(yytext); }
{SLCOM}         { charPos += strlen(yytext); }
{NEWLINE}       { ++linePos; charPos = 1; }
{WHITESPACE}    { ++charPos; }
{PUNC}          { printformat("-", yytext, "Punctuation");  ++charPos; }
{KEYWORD}       { printformat("-", yytext, "Keyword");      charPos += strlen(yytext); }
{ASSOP}         { printformat("-", yytext, "Assignment");   ++charPos; }
{ROPS}          { printformat("-", yytext, "Relational");   charPos += strlen(yytext); }
{AOPS}          { printformat("-", yytext, "Arithmetic");   ++charPos; }
{CLIT}          { printformat("-", yytext, "Literal");      charPos += 3; }
{SLIT}          { printformat("-", yytext, "Literal");      charPos += strlen(yytext); }
{DECLIT}        { printformat("-", yytext, "Literal");      charPos += strlen(yytext); }
{HEXLIT}        { printformat("-", yytext, "Literal");      charPos += strlen(yytext); }
{INTLIT}        { printformat("-", yytext, "Literal");      charPos += strlen(yytext); }
{IDEN}          { char* id = malloc(5); assignId(m, yytext, id);
                  printformat(id, yytext, "Identifier");
                  free(id);
                  charPos += strlen(yytext);
                }
%%

int yywrap() {
    return 1;
}

int main(void) {
    yyin = fopen("Vivek.c", "r");
    idmap.len = 0; charPos = linePos = 1;
    _printformat("ID", "Lexeme", "Type", "Position");
    printf("--------------------------------------------------------------------------------------------------\n");
    yylex();
    return 0;
}