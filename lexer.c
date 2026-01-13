#include "lexer.h"
#include "common.h"
#include <stdio.h>
#include <stdlib.h>

Lexer lexer;

static bool isWhitespace(char c) {
  switch (c) {
  case ' ':
  case '\r':
  case '\t':
  case '\n':
    return true;
  default:
    return false;
  }
}

static bool isDigit(char c) { return c >= '0' && c <= '9'; }

static int min(int a, int b) { return a < b ? a : b; }

static void growTokenArray() {
  lexer.capacity *= 2;
  lexer.tokens = realloc(lexer.tokens, lexer.capacity * sizeof(Token));
}

static Token makeNumberToken(const char *p) {
  Token t;

  int length = 1;
  while (isDigit(p[length])) {
    length += 1;
  }

  t.type = TOKEN_NUMBER;
  t.start = p;
  t.length = length;
  return t;
}

static Token makeToken(const char *p, TokenType type) {
  Token t;
  t.start = p;
  t.length = 1;
  t.type = type;
  return t;
}

static Token makeOperatorToken(const char *p) {

  switch (*p) {
  case '(':
    return makeToken(p, TOKEN_LEFT_PAREN);
  case ')':
    return makeToken(p, TOKEN_RIGHT_PAREN);
  case '+':
    return makeToken(p, TOKEN_PLUS);
  case '-':
    return makeToken(p, TOKEN_MINUS);
  case '*':
    return makeToken(p, TOKEN_STAR);
  case '/':
    return makeToken(p, TOKEN_SLASH);
  case '!':
    return makeToken(p, TOKEN_FACTORIAL);
  }

  printf("Error when parsing character %.*s.\n", 1, p);
  exit(65);
}

void initializeLexer(const char *input) {
  lexer.count = 0;
  lexer.capacity = 16;
  lexer.tokens = malloc(lexer.capacity * sizeof(Token));
  lexer.pos = 0;
  lexer.start = input;

  const char *p = input;
  while (*p != '\0') {

    if (isWhitespace(*p)) {
      p++;
      continue;
    }

    if (lexer.count == lexer.capacity) {
      growTokenArray();
    }

    Token t;

    if (isDigit(*p)) {
      t = makeNumberToken(p);
    } else {
      t = makeOperatorToken(p);
    }
    lexer.tokens[lexer.count++] = t;

    p += t.length;
  }

  if (lexer.count == lexer.capacity) {
    growTokenArray();
  }

  Token t;
  t.type = TOKEN_EOF;
  t.start = p;
  t.length = 1;
  lexer.tokens[lexer.count++] = t;
}

void freeLexer() {
  lexer.capacity = 0;
  lexer.count = 0;
  lexer.pos = 0;
  lexer.start = NULL;
  free(lexer.tokens);
}

Token peekToken() { return lexer.tokens[lexer.pos]; }

Token peekPreviousToken() { return lexer.tokens[lexer.pos - 1]; }

Token nextToken() {
  int idx = min(lexer.pos++, lexer.count - 1);
  return lexer.tokens[idx];
}