%{
    #include<stdio.h>
    #include<stdlib.h>
%}
%token A B
%start s
%%
s: c '\n' {return 0;}
c: a b;
a: A a;
a: ;
b: B b;
b: ;
%%

int main(void) {
    printf("Input: ");
    yyparse();
    printf("Valid!!\n");
    return 0;
} 
int yyerror() {
    printf("Invalid!!\n");
    exit(1);
}
