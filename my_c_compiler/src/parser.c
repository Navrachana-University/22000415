#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "parser.h"

extern Token *tokens;  // From lexer.c

// Function to create a new AST node
ASTNode* create_ast_node(NodeType type, char *value) {
    ASTNode *node = (ASTNode *)malloc(sizeof(ASTNode));
    node->type = type;
    node->value = value ? strdup(value) : NULL;
    node->left = NULL;
    node->right = NULL;
    return node;
}

// Function to parse the program
ASTNode* parse_program(Token *tokens, int *index, int token_count) {
    ASTNode *root = NULL;
    while (*index < token_count) {
        ASTNode *stmt = parse_statement(tokens, index);
        if (stmt) {
            if (root == NULL) {
                root = stmt;
            }
        }
    }
    return root;
}

// Function to parse statements
ASTNode* parse_statement(Token *tokens, int *index) {
    if (tokens[*index].type == TOKEN_INT) {
        return parse_var_declaration(tokens, index);
    }
    if (tokens[*index].type == TOKEN_IDENTIFIER) {
        if (tokens[*index + 1].type == TOKEN_ASSIGN) {
            return parse_var_assignment(tokens, index);
        } else if (tokens[*index + 1].type == TOKEN_LPAREN) {
            return parse_function_def(tokens, index);
        }
    }
    if (tokens[*index].type == TOKEN_RETURN) {
        return parse_return_statement(tokens, index);
    }
    if (tokens[*index].type == TOKEN_IF) {
        return parse_if_statement(tokens, index);
    }
    if (tokens[*index].type == TOKEN_WHILE) {
        return parse_while_statement(tokens, index);
    }
    return NULL;
}

// Function to parse variable declarations
ASTNode* parse_var_declaration(Token *tokens, int *index) {
    if (tokens[*index].type == TOKEN_INT) {
        (*index)++;
        if (tokens[*index].type == TOKEN_IDENTIFIER) {
            char *var_name = tokens[*index].lexeme;  // Changed from `value` to `lexeme`
            (*index)++;
            if (tokens[*index].type == TOKEN_ASSIGN) {
                (*index)++;
                if (tokens[*index].type == TOKEN_NUMBER) {
                    char *value = tokens[*index].lexeme;  // Changed from `value` to `lexeme`
                    (*index)++;
                    return create_ast_node(NODE_VAR_DECLARATION, var_name);
                }
            }
        }
    }
    return NULL;
}

// Function to parse variable assignments
ASTNode* parse_var_assignment(Token *tokens, int *index) {
    if (tokens[*index].type == TOKEN_IDENTIFIER) {
        char *var_name = tokens[*index].lexeme;  // Changed from `value` to `lexeme`
        (*index)++;
        if (tokens[*index].type == TOKEN_ASSIGN) {
            (*index)++;
            if (tokens[*index].type == TOKEN_NUMBER) {
                char *value = tokens[*index].lexeme;  // Changed from `value` to `lexeme`
                (*index)++;
                return create_ast_node(NODE_VAR_ASSIGNMENT, var_name);
            }
        }
    }
    return NULL;
}

// Function to parse function definitions
ASTNode* parse_function_def(Token *tokens, int *index) {
    if (tokens[*index].type == TOKEN_IDENTIFIER) {
        char *func_name = tokens[*index].lexeme;  // Changed from `value` to `lexeme`
        (*index)++;
        if (tokens[*index].type == TOKEN_LPAREN) {
            (*index)++;
            if (tokens[*index].type == TOKEN_RPAREN) {
                (*index)++;
                if (tokens[*index].type == TOKEN_LBRACE) {
                    (*index)++;
                    return create_ast_node(NODE_FUNCTION_DEF, func_name);
                }
            }
        }
    }
    return NULL;
}

// Function to parse return statements
ASTNode* parse_return_statement(Token *tokens, int *index) {
    if (tokens[*index].type == TOKEN_RETURN) {
        (*index)++;
        if (tokens[*index].type == TOKEN_IDENTIFIER || tokens[*index].type == TOKEN_NUMBER) {
            char *value = tokens[*index].lexeme;  // Changed from `value` to `lexeme`
            (*index)++;
            return create_ast_node(NODE_RETURN_STATEMENT, value);
        }
    }
    return NULL;
}

// Function to parse if statements
ASTNode* parse_if_statement(Token *tokens, int *index) {
    if (tokens[*index].type == TOKEN_IF) {
        (*index)++;
        if (tokens[*index].type == TOKEN_LPAREN) {
            (*index)++;
            ASTNode *condition = parse_expression(tokens, index);
            if (tokens[*index].type == TOKEN_RPAREN) {
                (*index)++;
                if (tokens[*index].type == TOKEN_LBRACE) {
                    (*index)++;
                    return create_ast_node(NODE_IF_STATEMENT, "if");
                }
            }
        }
    }
    return NULL;
}

// Function to parse while statements
ASTNode* parse_while_statement(Token *tokens, int *index) {
    if (tokens[*index].type == TOKEN_WHILE) {
        (*index)++;
        if (tokens[*index].type == TOKEN_LPAREN) {
            (*index)++;
            ASTNode *condition = parse_expression(tokens, index);
            if (tokens[*index].type == TOKEN_RPAREN) {
                (*index)++;
                if (tokens[*index].type == TOKEN_LBRACE) {
                    (*index)++;
                    return create_ast_node(NODE_WHILE_STATEMENT, "while");
                }
            }
        }
    }
    return NULL;
}

// Function to parse simple expressions (like variable names or numbers)
ASTNode* parse_expression(Token *tokens, int *index) {
    if (tokens[*index].type == TOKEN_IDENTIFIER || tokens[*index].type == TOKEN_NUMBER) {
        char *var_name = tokens[*index].lexeme;  // Changed from `value` to `lexeme`
        (*index)++;
        return create_ast_node(NODE_EXPRESSION, var_name);  // Changed from `lexeme` to `var_name`
    }
    return NULL;
}
