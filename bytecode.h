#ifndef BYTECODE_H
#define BYTECODE_H

#include <stdint.h>

typedef enum {
  INSTRUCTION_CONSTANT,
  INSTRUCTION_NEGATE,
  INSTRUCTION_FACTORIAL,
  INSTRUCTION_ADDITION,
  INSTRUCTION_SUBTRACT,
  INSTRUCTION_MULTIPLY,
  INSTRUCTION_DIVIDE
} InstructionType;

typedef struct {
  InstructionType type;
  double value;
} Instruction;

typedef struct {
  int count;
  int capacity;
  Instruction *instructions;
} Bytecode;

void initializeBytecode(Bytecode *byteCode);
void freeBytecode(Bytecode *byteCode);
void writeBytecode(Bytecode *bytecode, InstructionType type);
void writeBytecodeWithConstant(Bytecode *bytecode, InstructionType type,
                               double value);

#endif