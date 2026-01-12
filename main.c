#include "lexer.h"
#include "common.h"
#include <stdio.h>
#include "parser.h"

int main() {
    const char* input = "-2";
    initializeLexer(input);

    compile();
    return 0;
}