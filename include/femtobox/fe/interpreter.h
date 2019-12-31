#pragma once

/* STANDARD LIBRARY */
#include <stdint.h>

/* FEMTOBOX INCLUDES */
  /* FE INCLUDES */
  #include "femtobox/fe/instruction.h"

int16_t interpreter_execute(instruction_t* instr);
