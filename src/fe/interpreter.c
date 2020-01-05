#include "femtobox/fe/interpreter.h"

#include <string.h>

#include "femtobox/fe/instruction.h"

/* Public function implementations. */
int16_t interpreter_execute(instruction_t* instr)
{
  /* TODO: Generic code for instruction selection (use a lookup table) */
  // char const* instr_name = instruction_str(instr->opcode);
  // if (strncmp(instr_name, "NUL", INSTRUCTION_NAME_LENGTH) == 0)
  // {
  //   instr->result = 0;
  // }
  // else if (strncmp(instr_name, "NEG", INSTRUCTION_NAME_LENGTH) == 0)
  // {
  //   instr->result = -interpreter_execute(instr->arguments[0]);
  // }
  // else if (strncmp(instr_name, "ADD", INSTRUCTION_NAME_LENGTH) == 0)
  // {
  //   uint16_t sum = interpreter_execute(instr->arguments[0]);
  //   for (int i = 1; i < INSTRUCTION_MAX_ARGUMENTS; ++i)
  //   {
  //     if (instr->arguments[i])
  //     {
  //       sum += interpreter_execute(instr->arguments[i]);
  //     }
  //     else
  //     {
  //       break;
  //     }
  //   }
  //   instr->result = sum;
  // }
  return instr->result;
}
