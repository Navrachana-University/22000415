#ifndef PARSER_H
#define PARSER_H

#include "lexer.h"

typedef enum {
    NODE_VAR_DECLARATION,
    NODE_VAR_ASSIGNMENT,
    NODE_FUNCTION_DEF,
    NODE_RETURN_STATEMENT,
    NODE_IF_STATEMENT,
    NODE_WHILE_STATEMENT,
    NODE_EXPRESSION
} NodeType;

typedef struct ASTNode {
    NodeType type;
    char *value;
    struct ASTNode *left;
    struct ASTNode *right;
} ASTNode;

// Function Declarations
ASTNode* parse_program(Token *tokens, int *index, int token_count);
ASTNode* parse_statement(Token *tokens, int *index);
ASTNode* parse_var_declaration(Token *tokens, int *index);
ASTNode* parse_var_assignment(Token *tokens, int *index);
ASTNode* parse_function_def(Token *tokens, int *index);
ASTNode* parse_return_statement(Token *tokens, int *index);
ASTNode* parse_if_statement(Token *tokens, int *index);
ASTNode* parse_while_statement(Token *tokens, int *index);
ASTNode* parse_expression(Token *tokens, int *index);

#endif
