#include <stdio.h>
#include <stdlib.h>

#include "lexer.h"

int main(int argc, char *argv[]) {
    if (argc < 2) {
        printf("Usage: %s <source_file>\n", argv[0]);
        return 1;
    }

    FILE *file = fopen(argv[1], "r");
    if (!file) {
        perror("Failed to open file");
        return 1;
    }

    fseek(file, 0, SEEK_END);
    long length = ftell(file);
    rewind(file);

    char *source = (char *)malloc(length + 1);
    fread(source, 1, length, file);
    source[length] = '\0';
    fclose(file);

    Lexer lexer;
    init_lexer(&lexer, source);

    Token token;
    do {
        token = get_next_token(&lexer);
        printf("Token: Type=%d, Lexeme='%s'\n", token.type, token.lexeme);
        free(token.lexeme);
    } while (token.type != TOKEN_EOF);

    free(source);
    return 0;
}
