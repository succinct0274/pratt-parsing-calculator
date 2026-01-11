#include "lexer.h"
#include "common.h"
#include <stdio.h>

int main() {
    const char* input = "-2 + 3";
    initializeLexer(input);

    Token t = nextToken();
    while (t.type != TOKEN_EOF) {
        printf("[%s] %.*s\n", tokenTypeNames[t.type], (int) t.length, t.start);
        t = nextToken();
    }
    return 0;
}