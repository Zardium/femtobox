#pragma once

#include <stdint.h>

#define INSTRUCTION_NAME_LENGTH 3
#define INSTRUCTION_MAX_ARGUMENTS 4

typedef struct instruction
{
  uint16_t opcode;
  int16_t  result;
  uint16_t argument_count;
  struct instruction* arguments[INSTRUCTION_MAX_ARGUMENTS];
} instruction_t;

instruction_t* instruction_alloc(uint16_t opcode);

void instruction_free(instruction_t**);

uint16_t instruction_opcode(char const* str);

char const* instruction_str(uint16_t opcode);