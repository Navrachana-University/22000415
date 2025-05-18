%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
extern FILE *yyin;
extern FILE *yyout;
int yylex(void);
void yyerror(char *);
char* newTemp();

int tempCount = 1;

%}

%union {
    char* str;
}

%token <str> ID
%token <str> NUMBER
%type <str> E T F

%%
S : ID '=' E ';' {
        fprintf(yyout,"%s = %s\n", $1, $3);
    }
  ;

E : E '+' T {
        char* temp = newTemp();
        fprintf(yyout,"%s = %s + %s\n", temp, $1, $3);
        $$ = temp;
    }
  | T {
        $$ = $1;
    }
  ;

T : T '*' F {
        char* temp = newTemp();
        fprintf(yyout,"%s = %s * %s\n", temp, $1, $3);
        $$ = temp;
    }
  | F {
        $$ = $1;
    }
  ;

F : ID {
        $$ = $1;
    }
  | NUMBER {
        char* temp = newTemp();
        fprintf(yyout,"%s = %s\n", temp, $1);
        $$ = temp;
    }
  ;
%%

char* newTemp() {
    char buffer[10];
    sprintf(buffer, "t%d", tempCount++);
    return strdup(buffer);
}

void yyerror(char *s) {
    fprintf(stderr, "Error: %s\n", s);
}

int main() {
yyin= fopen("input.txt","r");
yyout= fopen("output.txt","w");
    yyparse();
    return 0;
}
