%{

#include <stdio.h>

int lines   = 0;

%}
%%


\n  { lines++; }
. 
%%



int main(void) {
    yyin= fopen("Vivek.txt","r");
    yylex();
    printf("Lines:  %3d\n", lines);
    return 0;
}

int yywrap() {
    return 1;
}
