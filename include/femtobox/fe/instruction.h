#pragma once

#include <stdint.h>

#define INSTRUCTION_MAX_ARGUMENTS 4

typedef enum opcode
{
  ERR = -1,
  NUL,
  VAL,
  NEG,
  ADD,

  OPCODE_COUNT,
} opcode_t;

extern char const* opcode_names[];

typedef struct instruction
{
  uint16_t opcode;
  int16_t  result;
  uint16_t argument_count;
  struct instruction* arguments[INSTRUCTION_MAX_ARGUMENTS];
} instruction_t;

instruction_t* instruction_alloc(uint16_t opcode);

void instruction_free(instruction_t**);

opcode_t opcode_from_string(char const* name);
