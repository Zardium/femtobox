#pragma once

#include "femtobox/fe/token.h"

/*!
\brief Splits an input string into a series of Fe tokens.
       ALLOCATES MEMORY. Free tokens when done.

\param input A string of textual Fe instructions.
\param[out] token_count Returns the number of tokens.
\return token_t* Returns pointer to the first token in an array.
 */
token_t* lexer_tokenize(char const* input);

