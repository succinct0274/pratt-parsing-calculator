#include "common.h"
#include <stddef.h>

#ifndef LEXER_H
#define LEXER_H

typedef struct {
    const char *start;
    Token* tokens;
    size_t count;
    size_t capacity;
    size_t pos;
} Lexer;

void initializeLexer(const char* input);
void freeLexer();
Token peekToken();
Token nextToken();

#endif