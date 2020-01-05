#include "femtobox/fe/token.h"

#include <stdio.h>
#include <stdlib.h> /* calloc */

#include "femtobox/fe/instruction.h" /* opcode_names */

token_t* token_alloc(token_type_t type, uint16_t value)
{
  token_t* new_token = calloc(1, sizeof(token_t));
  new_token->type = type;
  if (type == token_integer || type == token_instruction)
  {
    new_token->value = value;
  }
  return new_token;
}

int token_free(token_t** token)
{
  free(*token);
  *token = NULL;
  return 1;
}

int token_free_list(token_t** token_list)
{
  if (!(*token_list)->next)
  {
    return token_free(token_list);
  }
  return token_free_list(&(*token_list)->next) + 1;
}

void token_print_list(token_t* token_list)
{
  while (token_list)
  {
    switch (token_list->type)
    {
      case token_comma:
        fputs("[COMMA] ", stdout);
        break;
      case token_paren_l:
        fputs("[LEFT PAREN] ", stdout);
        break;
      case token_paren_r:
        fputs("[RIGHT PAREN] ", stdout);
        break;
      case token_integer:
        printf("[INTEGER]:{%u} ", token_list->value);
        break;
      case token_instruction:
        printf("[INSTRUCTION]:{%s} ", opcode_names[token_list->value]);
        break;
      default:
        break;
    }
    token_list = token_list->next;
  }
  puts("");
}
