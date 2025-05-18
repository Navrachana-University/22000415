%{
#include "n.tab.h"
#include <string.h>
%}

%%

[0-9]+       { yylval.str = strdup(yytext); return NUMBER; }
[a-zA-Z_][a-zA-Z0-9_]*   { yylval.str = strdup(yytext); return ID; }
"="          return '=';
";"          return ';';
"+"          return '+';
"*"          return '*';
[ \t\n]      ;   // skip whitespace
.            { printf("Unknown character: %s\n", yytext); }

%%

int yywrap() {
    return 1;
}
