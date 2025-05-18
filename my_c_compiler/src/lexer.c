#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "lexer.h"

// Custom implementation of strndup for Windows
char *strndup(const char *str, size_t n) {
    size_t len = strnlen(str, n);
    char *copy = (char *)malloc(len + 1);
    if (copy) {
        memcpy(copy, str, len);
        copy[len] = '\0';
    }
    return copy;
}

static const char* keywords[] = {
    "int", "return", "if", "else", "while", "for", "continue", "break", "switch", "case", "default", "struct"
};

static TokenType keyword_token_types[] = {
    TOKEN_INT, TOKEN_RETURN, TOKEN_IF, TOKEN_ELSE, TOKEN_WHILE, TOKEN_FOR,
    TOKEN_CONTINUE, TOKEN_BREAK, TOKEN_SWITCH, TOKEN_CASE, TOKEN_DEFAULT, TOKEN_STRUCT
};

static Token make_token(TokenType type, const char* start, int length) {
    Token token;
    token.type = type;
    token.lexeme = strndup(start, length);
    return token;
}

static void skip_whitespace(Lexer* lexer) {
    while (isspace(lexer->src[lexer->pos])) lexer->pos++;
}

void init_lexer(Lexer* lexer, const char* src) {
    lexer->src = src;
    lexer->pos = 0;
}

Token get_next_token(Lexer* lexer) {
    skip_whitespace(lexer);
    const char* src = lexer->src;
    int i = lexer->pos;

    if (src[i] == '\0') return make_token(TOKEN_EOF, "", 0);

    // Identifiers and keywords
    if (isalpha(src[i]) || src[i] == '_') {
        int start = i;
        while (isalnum(src[i]) || src[i] == '_') i++;
        int len = i - start;
        lexer->pos = i;
        for (int k = 0; k < sizeof(keywords)/sizeof(keywords[0]); ++k) {
            if (strncmp(&src[start], keywords[k], len) == 0 && strlen(keywords[k]) == len) {
                return make_token(keyword_token_types[k], &src[start], len);
            }
        }
        return make_token(TOKEN_IDENTIFIER, &src[start], len);
    }

    // Numbers
    if (isdigit(src[i])) {
        int start = i;
        while (isdigit(src[i])) i++;
        lexer->pos = i;
        return make_token(TOKEN_NUMBER, &src[start], i - start);
    }

    // Single character tokens
    lexer->pos++;
    switch (src[i]) {
        case '(': return make_token(TOKEN_LPAREN, "(", 1);
        case ')': return make_token(TOKEN_RPAREN, ")", 1);
        case '{': return make_token(TOKEN_LBRACE, "{", 1);
        case '}': return make_token(TOKEN_RBRACE, "}", 1);
        case ';': return make_token(TOKEN_SEMICOLON, ";", 1);
        case ',': return make_token(TOKEN_COMMA, ",", 1);
        case '+': return make_token(TOKEN_PLUS, "+", 1);
        case '-': return make_token(TOKEN_MINUS, "-", 1);
        case '*': return make_token(TOKEN_STAR, "*", 1);
        case '/': return make_token(TOKEN_SLASH, "/", 1);
        case '=':
            if (src[i+1] == '=') { lexer->pos++; return make_token(TOKEN_EQ, "==", 2); }
            return make_token(TOKEN_ASSIGN, "=", 1);
        case '!':
            if (src[i+1] == '=') { lexer->pos++; return make_token(TOKEN_NEQ, "!=", 2); }
            break;
        case '<':
            if (src[i+1] == '=') { lexer->pos++; return make_token(TOKEN_LE, "<=", 2); }
            return make_token(TOKEN_LT, "<", 1);
        case '>':
            if (src[i+1] == '=') { lexer->pos++; return make_token(TOKEN_GE, ">=", 2); }
            return make_token(TOKEN_GT, ">", 1);
    }

    return make_token(TOKEN_UNKNOWN, &src[i], 1);
}

// Helper function to create a new token
void create_token(Token *tokens, int *index, int type, const char *value) {
    tokens[*index].type = type;
    tokens[*index].lexeme = strdup(value);
    (*index)++;
}

// Main tokenization function
int tokenize(const char *source, Token *tokens) {
    int index = 0;  // Token index
    int length = strlen(source);
    int i = 0;

    while (i < length) {
        if (isspace(source[i])) {
            // Skip whitespace
            i++;
        }
        else if (isalpha(source[i])) {
            // Handle keywords and identifiers
            int start = i;
            while (isalnum(source[i])) {
                i++;
            }
            int len = i - start;
            char *word = strndup(source + start, len);
            if (strcmp(word, "int") == 0) {
                create_token(tokens, &index, TOKEN_INT, word);
            } else if (strcmp(word, "return") == 0) {
                create_token(tokens, &index, TOKEN_RETURN, word);
            } else {
                create_token(tokens, &index, TOKEN_IDENTIFIER, word);
            }
            free(word);  // Free the temporary word buffer
        }
        else if (isdigit(source[i])) {
            // Handle numbers
            int start = i;
            while (isdigit(source[i])) {
                i++;
            }
            int len = i - start;
            char *num_str = strndup(source + start, len);
            create_token(tokens, &index, TOKEN_NUMBER, num_str);
            free(num_str);
        }
        else if (source[i] == '+') {
            create_token(tokens, &index, TOKEN_PLUS, "+");
            i++;
        }
        else if (source[i] == '-') {
            create_token(tokens, &index, TOKEN_MINUS, "-");
            i++;
        }
        else if (source[i] == '*') {
            create_token(tokens, &index, TOKEN_MULTIPLY, "*");
            i++;
        }
        else if (source[i] == '/') {
            create_token(tokens, &index, TOKEN_DIVIDE, "/");
            i++;
        }
        else if (source[i] == '(') {
            create_token(tokens, &index, TOKEN_LPAREN, "(");
            i++;
        }
        else if (source[i] == ')') {
            create_token(tokens, &index, TOKEN_RPAREN, ")");
            i++;
        }
        else if (source[i] == '{') {
            create_token(tokens, &index, TOKEN_LBRACE, "{");
            i++;
        }
        else if (source[i] == '}') {
            create_token(tokens, &index, TOKEN_RBRACE, "}");
            i++;
        }
        else if (source[i] == ';') {
            create_token(tokens, &index, TOKEN_SEMICOLON, ";");
            i++;
        }
        else {
            // If we encounter an unknown character, skip it (or handle error)
            i++;
        }
    }

    // Return the number of tokens
    return index;
}
