#include "bytecode.h"
#include <stdlib.h>

void initializeBytecode(Bytecode* bytecode) {
    bytecode->count = 0;
    bytecode->capacity = 8;
    bytecode->instructions = realloc(bytecode->instructions, sizeof(Instruction) * bytecode->capacity);
}

void freeBytecode(Bytecode* bytecode) {

    free(bytecode->instructions);
    initializeBytecode(bytecode);
}

void writeBytecode(Bytecode *bytecode, InstructionType type) {
    if (bytecode->capacity < bytecode->count + 1) {
        int oldCapacity = bytecode->capacity;
        bytecode->capacity = oldCapacity * 2;
        bytecode->instructions = realloc(bytecode->instructions, sizeof(Instruction) * bytecode->capacity);
    }

    Instruction instruction = {
        .type = type,
        .value = 0.0
    };
    bytecode->instructions[bytecode->count++] = instruction;
}

void writeBytecodeWithConstant(Bytecode *bytecode, InstructionType type, double value) {
    writeBytecode(bytecode, type);
    bytecode->instructions[bytecode->count - 1].value = value;
}