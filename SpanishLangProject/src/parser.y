%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int yylex(void);
void yyerror(const char *msg);

void assign(char *a, char *b) {
    printf("%s = %s\n", a, b);
}

void print(char *a) {
    printf("imprimir %s\n", a);
}

void if_else(char *cond, char *true_part, char *false_part) {
    printf("si (%s) { %s } sino { %s }\n", cond, true_part, false_part);
}

void for_loop(char *init, char *cond, char *update, char *body) {
    printf("para (%s; %s; %s) { %s }\n", init, cond, update, body);
}

void switch_case(char *expr, char *case_body) {
    printf("caso (%s) { %s }\n", expr, case_body);
}
%}

%union {
    char *str;
}

%token <str> IDENTIFIER NUMBER BOOLEAN
%token TK_NUM TK_BOOL TK_PRINT TK_IF TK_ELSE TK_FOR TK_CASE TK_BREAK
%token ASSIGN SEMICOLON LBRACE RBRACE LPAREN RPAREN

%type <str> expression statement

%%

program:
    program statement
    | statement
    ;

statement:
    TK_NUM IDENTIFIER SEMICOLON
    | TK_BOOL IDENTIFIER SEMICOLON
    | IDENTIFIER ASSIGN expression SEMICOLON {
        assign($1, $3);
    }
    | TK_PRINT IDENTIFIER SEMICOLON {
        print($2);
    }
    | TK_IF LPAREN expression RPAREN LBRACE statement RBRACE TK_ELSE LBRACE statement RBRACE {
        if_else($3, $6, $10);
    }
    | TK_FOR LPAREN IDENTIFIER ASSIGN expression SEMICOLON expression SEMICOLON IDENTIFIER ASSIGN expression RPAREN LBRACE statement RBRACE {
        for_loop($3, $5, $7, $11);
    }
    | TK_CASE LPAREN expression RPAREN LBRACE statement RBRACE {
        switch_case($3, $6);
    }
    ;

expression:
    NUMBER         { $$ = $1; }
    | IDENTIFIER   { $$ = $1; }
    | BOOLEAN      { $$ = $1; }
    ;

%%

int main() {
    return yyparse();
}

void yyerror(const char *msg) {
    fprintf(stderr, "Error de sintaxis: %s\n", msg);
}
