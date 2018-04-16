%{
#include<ctype.h>
#include<stdio.h>
#define YYSTYPE double
%}
%token id
%left '+' '-'
%left '*' '/'
%right um

%%
S : S E '\n' {printf("Result: %g \nExpression: ", $2); }
S : S '\n';
S : ;
S : error '\n' { yyerror("Error!!\n" ); yyerrok; };
E : E '+' E { $$ = $1 + $3; };
E : E '-' E { $$ = $1 - $3; };
E : E '*' E { $$ = $1 * $3; };
E : E '/' E { $$ = $1 / $3; };
E : '(' E ')' { $$ = $2; };
E : '-' E %prec um { $$ = -$2; };
E : id;
%%

int main() {
    printf("Enter expression: ");
    yyparse();
}
int yyerror (char * s) {
    printf ("% s \n", s);
    exit (1);
}
