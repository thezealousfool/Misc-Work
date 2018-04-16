%{
#include "y.tab.c"
%}
D [0-9]+\.?|[0-9]*\.[0-9]+

%option noyywrap

%%
[ ]
{D} { yylval = atof(yytext); return id; }
\n|. { return yytext[0]; }
%%
