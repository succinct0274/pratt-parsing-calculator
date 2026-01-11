#ifndef COMMON_H
#define COMMON_H

#include <stdbool.h>

typedef enum {
    TOKEN_NUMBER,
    TOKEN_OP,
    TOKEN_EOF
} TokenType;

typedef struct {
    TokenType type;
    const char* start;
    int length;
} Token;

extern const char* tokenTypeNames[];

#endif