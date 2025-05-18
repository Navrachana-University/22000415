#ifndef LEXER_H
#define LEXER_H

#include <stddef.h>

// Define Token Types
typedef enum {
    TOKEN_INT,
    TOKEN_RETURN,
    TOKEN_IDENTIFIER,
    TOKEN_NUMBER,
    TOKEN_LPAREN,
    TOKEN_RPAREN,
    TOKEN_LBRACE,
    TOKEN_RBRACE,
    TOKEN_SEMICOLON,
    TOKEN_PLUS,
    TOKEN_MINUS,
    TOKEN_MULTIPLY,
    TOKEN_DIVIDE,
    TOKEN_ASSIGN,
    TOKEN_EQ,
    TOKEN_NEQ,
    TOKEN_LT,
    TOKEN_GT,
    TOKEN_LE,
    TOKEN_GE,
    TOKEN_UNKNOWN,
    TOKEN_EOF, TOKEN_IF, TOKEN_ELSE, TOKEN_WHILE, TOKEN_FOR,
    TOKEN_CONTINUE, TOKEN_BREAK, TOKEN_SWITCH, TOKEN_CASE, TOKEN_DEFAULT, TOKEN_STRUCT,
    TOKEN_COMMA,
      TOKEN_STAR,TOKEN_SLASH
} TokenType;

// Define Token structure
typedef struct {
    TokenType type;
    char* lexeme;  // This is where the lexeme will be stored
} Token;

// Define Lexer structure
typedef struct {
    const char* src;
    int pos;
} Lexer;

// Function prototypes
void init_lexer(Lexer* lexer, const char* src);
Token get_next_token(Lexer* lexer);

#endif  // LEXER_H