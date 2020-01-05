#include "femtobox/fe/lexer.h"

#include <string.h> /* strncmp */
#include <ctype.h>  /* toupper, isspace, isalpha, isdigit */
#include <stdlib.h> /* atoi */

#include "femtobox/fe/instruction.h" /* opcode_from_string */

/* Private function declarations. */

static char const* skip_whitespace(char const* it);

static token_t* consume_instruction(char const** it);

static token_t* consume_integer(char const** it);

/* Public function implementations. */

token_t* lexer_tokenize(char const* input)
{
  token_t* head = NULL;
  token_t* tail = NULL;
  char const* it = input;
  while (*it)
  {
    token_t* new_token = NULL;
    it = skip_whitespace(it);
    if (isdigit(*it))
    {
      new_token = consume_integer(&it);
    }
    else if (isalpha(*it))
    {
      new_token = consume_instruction(&it);
    }
    else
    {
      switch (*it)
      {
        case ',':
          new_token = token_alloc(token_comma, 0);
          break;
        case '(':
          new_token = token_alloc(token_paren_l, 0);
          break;
        case ')':
          new_token = token_alloc(token_paren_r, 0);
          break;
        default: // TODO: stick an error instruction in here
          break;
      }
      ++it;
    }
    /* So no head? */
    if (!head)
    {
      head = new_token;
      tail = new_token;
    }
    else
    {
      tail->next = new_token;
      tail = tail->next;
    }
  }
  return head;
}

/* Private function implementations. */

static char const* skip_whitespace(char const* it)
{
  while (isspace(*it))
  {
    ++it;
  }
  return it;
}

static token_t* consume_instruction(char const** it)
{
  char const* begin = *it;
  while (isalpha(**it))
  {
    ++(*it);
  }
  size_t name_length = *it - begin;
  /* +1 to account for NUL-terminator. */
  char buffer[name_length + 1];
  strncpy(buffer, begin, name_length);
  buffer[name_length] = '\0';

  return token_alloc(token_instruction, opcode_from_string(buffer));
}

static token_t* consume_integer(char const** it)
{
  char const* begin = *it;
  while (isdigit(**it))
  {
    ++(*it);
  }
  size_t digit_count = *it - begin;
  /* +1 to account for NUL-terminator. */
  char buffer[digit_count + 1];
  strncpy(buffer, begin, digit_count);
  buffer[digit_count] = '\0';

  return token_alloc(token_integer, atoi(buffer));
}
