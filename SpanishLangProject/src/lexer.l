%{
#include "parser.tab.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int yylex(void);
void yyerror(const char *s);

char *strdup(const char *str) {
    char *copy = malloc(strlen(str) + 1);
    if (copy) {
        strcpy(copy, str);
    }
    return copy;
}
%}

%%
"número"               { return TK_NUM; }
"booleano"             { return TK_BOOL; }
"verdadero"            { yylval.str = strdup("true"); return BOOLEAN; }
"falso"                { yylval.str = strdup("false"); return BOOLEAN; }
"imprimir"             { return TK_PRINT; }
"si"                   { return TK_IF; }
"sino"                 { return TK_ELSE; }
"para"                 { return TK_FOR; }
"caso"                 { return TK_CASE; }
"romper"               { return TK_BREAK; }
[0-9]+                 { yylval.str = strdup(yytext); return NUMBER; }
[a-zA-Z_][a-zA-Z0-9_]* { yylval.str = strdup(yytext); return IDENTIFIER; }
"="                    { return ASSIGN; }
";"                    { return SEMICOLON; }
"{"                    { return LBRACE; }
"}"                    { return RBRACE; }
"("                    { return LPAREN; }
")"                    { return RPAREN; }
[ \t\n]+               ;  // Skip whitespace
.                      { printf("Unknown character: %s\n", yytext); }

%%

int yywrap(void) {
    return 1;  // End of input, return true
}
