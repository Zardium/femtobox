#include "timing.h" /* Declarations. */

/* EXTERNAL LIBRARIES */
#include <SDL2/SDL.h> /* SDL_GetTicks, SDL_Delay */

/* Public function implementations. */

size_t timing_get_ticks()
{
  return SDL_GetTicks();
}

void timing_delay(size_t ms)
{
  SDL_Delay(ms);
}
