INT     [0-9]+
DEC     [0-9]+\.[0-9]+

%{
#include<stdio.h>

int integers    = 0,
    floats      = 0;

%}

%%
{INT}   { ++integers; }
{DEC}   { ++floats; }
\n      ;
.       ;
%%



int main(void) {
    yyin = fopen("Vivek.txt", "r");
    yylex();

    printf("Integers:           %d\n", integers);
    printf("Floating Points:    %d\n", floats);

    return 0;
}

int yywrap() {
    return 1;
}
