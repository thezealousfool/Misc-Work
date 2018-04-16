%{
#include<stdio.h>

int lines   = 0,
    words   = 0,
    chars   = 0;

%}
%%

 
\n          { lines++; words++; }
[\t ' ']    words++;
.           chars++;
%%



int main(void) {
    yyin = fopen("Vivek.txt", "r");
    yylex();

    printf("Lines:      %5d\n", lines);
    printf("Words:      %5d\n", words);
    printf("Characters: %5d\n", chars);

    return 0;
}

int yywrap() {
    return 1;
}
