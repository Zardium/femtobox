#include "femtobox/fe/lexer.h"

#include <string.h> /* strncmp */
#include <ctype.h>  /* toupper, isspace */
#include <stdlib.h> /* atoi */

/* Private function declarations. */

char const* skip_whitespace_(char const* it);

char const* iterate_to_(char const* it, char c);

/* Public function implementations. */

instruction_t* lexer_read(char const* str_input)
{
  /* Iterator. */
  char const* it = NULL;

  uint16_t opcode = instruction_opcode(str_input);
  if (opcode == UINT16_MAX)
  {
    return NULL;
  }

  instruction_t* instr = instruction_alloc(opcode);

  it = str_input + INSTRUCTION_NAME_LENGTH;
  if ((*it) == '\0')
  {
    return NULL;
  }
  it = skip_whitespace_(it);
  
  /* TODO: Generic code for instruction selection (use a lookup table) */
  if (strncmp(instruction_str(opcode), "VAL", INSTRUCTION_NAME_LENGTH) == 0)
  {
    instr->result = atoi(it);
    return instr;
  }

  while (*it)
  {
    switch (*it)
    {
      case '(':
        instr->arguments[instr->argument_count++] = lexer_read(it + 1);
        it = iterate_to_(it, ')');
        break;
      default:
        ++it;
        break;
    }
  }

  return instr;
}

/* Private function implementations. */

char const* skip_whitespace_(char const* it)
{
  while (isspace(*it))
  {
    ++it;
  }
  return it;
}

/* TODO: make this safe */
char const* iterate_to_(char const* it, char c)
{
  while (*it != c)
  {
    ++it;
  }
  return it;
}
