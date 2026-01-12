#ifndef PARSER_H
#define PARSER_H

typedef enum {
    PREC_NONE,
    PREC_TERM,
    PREC_FACTOR,
    PREC_UNARY,
    PREC_FACTORIAL,
    PREC_PRIMARY,
} ParsePrecedence;

typedef void (*ParseFn)();

typedef struct {
    ParseFn prefix;
    ParseFn infix;
    ParsePrecedence precedence;
} ParseRule;

void compile();

#endif