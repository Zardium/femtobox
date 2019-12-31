#include "femtobox/fe/instruction.h"

#define __USE_MINGW_ANSI_STDIO 1 /* mingw msvcrt compatibiltity */

#include <stdio.h>
#include <string.h>
#include <stdlib.h> /* calloc */

/* Instruction set loaded at compile time. */
extern char  _binary_data_instructions_start[];
extern char  _binary_data_instructions_end[];
extern char *_binary_data_instructions_size;

#define INSTRUCTION_COUNT ((uintptr_t)&_binary_data_instructions_size) / (INSTRUCTION_NAME_LENGTH + 1)

/* Private function declarations. */

/* Public function implementations. */

instruction_t* instruction_alloc(uint16_t opcode)
{
  instruction_t* instr = calloc(1, sizeof(instruction_t));
  instr->opcode = opcode;
  return instr;
}

void instruction_free(instruction_t** instr)
{
  free(*instr);
  *instr = NULL;
}

uint16_t instruction_opcode(char const* str)
{
  for (uint16_t i = 0; i < INSTRUCTION_COUNT; ++i)
  {
    if (strncmp(str, instruction_str(i), INSTRUCTION_NAME_LENGTH) == 0)
    {
      return i;
    }
  }
  return UINT16_MAX;
}

char const* instruction_str(uint16_t opcode)
{
  if (opcode != UINT16_MAX)
  {
    size_t offset = opcode * (INSTRUCTION_NAME_LENGTH + 1);
    /* NUL-terminate the string. */
    _binary_data_instructions_start[offset + INSTRUCTION_NAME_LENGTH] = '\0';
    return _binary_data_instructions_start + offset;
  }
  else
  {
    return "NUL";
  }
}

/* Private function implementations. */

