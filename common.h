#ifndef COMMON_H
#define COMMON_H

#include <stdbool.h>
#include <stddef.h>

#define MIN(a,b) ((a) < (b) ? (a) : (b));

typedef enum {
    TOKEN_NUMBER,
    TOKEN_LEFT_PAREN,
    TOKEN_RIGHT_PAREN,
    TOKEN_PLUS,
    TOKEN_MINUS,
    TOKEN_STAR,
    TOKEN_SLASH,
    TOKEN_FACTORIAL,
    TOKEN_EOF
} TokenType;

typedef struct {
    TokenType type;
    const char* start;
    int length;
} Token;

extern const char* tokenTypeNames[];

#endif