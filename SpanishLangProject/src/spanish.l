%{
#include "spanish.tab.h"
#include <string.h>
%}

%%

[0-9]+                      { yylval.str = strdup(yytext); return NUMBER; }
[a-zA-Z_áéíóúñÁÉÍÓÚÑ][a-zA-Z0-9_]* { yylval.str = strdup(yytext); return ID; }

"="                        return '=';
";"                        return ';';
"+"                        return '+';
"*"                        return '*';

[ \t\n]                    ; // skip whitespace
.                          { printf("Caracter desconocido: %s\n", yytext); }

%%

int yywrap() { return 1; }
