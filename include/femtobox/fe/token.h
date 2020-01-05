#pragma once

#include <stdint.h>

typedef enum token_type
{
  token_comma,   /*  ,   */
  token_paren_l, /*  \(  */
  token_paren_r, /*  \)  */
  token_integer, /* [0-9]* */
  token_instruction,    /* ([a-z]|[A-Z])* */

} token_type_t;

typedef struct token
{
  token_type_t type;
  uint16_t value;
  struct token* next;
} token_t;

token_t* token_alloc(token_type_t type, uint16_t value);

int token_free(token_t** token);

int token_free_list(token_t** token_list);

void token_print_list(token_t* token_list);
