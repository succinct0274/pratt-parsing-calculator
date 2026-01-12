#include "parser.h"
#include "bytecode.h"
#include "common.h"
#include "lexer.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

static void expression();
static void grouping();
static void negate();
static void number();
static void parse(ParsePrecedence precedence);
static void emitInstruction(InstructionType type);
static void emitInstructionWithConstant(InstructionType type, double value);

Bytecode bytecode;

ParseRule rules[] = {
    [TOKEN_NUMBER] = { .prefix=number, .infix=NULL, .precedence=PREC_PRIMARY },
    [TOKEN_LEFT_PAREN] = { .prefix=grouping, .infix=NULL, .precedence=PREC_NONE},
    [TOKEN_RIGHT_PAREN] = {.prefix=NULL, .infix=NULL, .precedence=PREC_NONE},
    [TOKEN_PLUS] = {.prefix=NULL, .infix=NULL, .precedence=PREC_TERM},
    [TOKEN_MINUS] = {.prefix=negate, .infix=NULL, .precedence=PREC_TERM},
    [TOKEN_STAR] = {.prefix=NULL, .infix=NULL, .precedence=PREC_FACTOR},
    [TOKEN_SLASH] = {.prefix=NULL, .infix=NULL, .precedence=PREC_FACTOR},
    [TOKEN_FACTORIAL] = {.prefix=NULL, .infix=NULL, .precedence=PREC_FACTORIAL},
    [TOKEN_EOF] = {.prefix=NULL, .infix=NULL, .precedence=PREC_NONE},
};

static ParseRule *getRule(TokenType type) { return &rules[type]; }

static void emitInstruction(InstructionType op) {
    writeBytecode(&bytecode, op);
}

static void emitInstructionWithConstant(InstructionType op, double value) {
    writeBytecodeWithConstant(&bytecode, op, value);
}

static void expression() {
    parse(PREC_TERM);
}

static void grouping() {
    
    expression();

    // Consume right parenthesis
    Token current = nextToken();
    if (current.type != TOKEN_RIGHT_PAREN) {
        fprintf(stderr, "Expect ')' but receive %.*s.\n", current.length, current.start);
        exit(EXIT_FAILURE);
    }
}

static void negate() {

    parse(PREC_UNARY);
    emitInstruction(INSTRUCTION_NEGATE);
}

static void number() {
    Token token = peekPreviousToken();
    double value = strtod(token.start, NULL);
    emitInstructionWithConstant(INSTRUCTION_CONSTANT, value);
}

static void parse(ParsePrecedence precedence) {
    Token token = nextToken();

    ParseFn prefixFn = getRule(token.type)->prefix;
    
    // Execute the function when this token acts as the prefix
    prefixFn();

    while (getRule(peekToken().type)->precedence >= precedence) {
        // Calling next token is because all function (both unary and binary) deal with the previous token
        nextToken();
        ParseFn infixFn = getRule(peekPreviousToken().type)->infix;
        infixFn();
    }
}

void compile() {
    initializeBytecode(&bytecode);
    expression();

    freeBytecode(&bytecode);
}
