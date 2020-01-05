#include "femtobox/fe/instruction.h"

#define __USE_MINGW_ANSI_STDIO 1 /* mingw msvcrt compatibiltity */

#include <stdio.h>
#include <string.h>
#include <stdlib.h> /* calloc */

/* Public variable definitions. */

char const* opcode_names[] =
{
  "NUL",
  "VAL",
  "NEG",
  "ADD",
};

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

opcode_t opcode_from_string(char const* name)
{
  for (int i = 0; i < OPCODE_COUNT; ++i)
  {
    if (strcmp(name, opcode_names[i]) == 0)
    {
      return (opcode_t)i;
    }
  }
  return ERR;
}

/* Private function implementations. */

