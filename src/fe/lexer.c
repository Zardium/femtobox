#include "femtobox/fe/lexer.h"

#include <ctype.h> /* toupper, isspace */

/* Private function declarations. */



/* Public function implementations. */

instruction_t* lexer_read(char const* str_input)
{
  /* Iterator. */
  //char const* it = NULL;

  uint16_t opcode = instruction_opcode(str_input);
  if (opcode == UINT16_MAX)
  {
    return NULL;
  }

  instruction_t* instr = instruction_alloc(opcode);

  return instr;
}

/* Private function implementations. */


