/* STANDARD LIBRARIES */
#include <stdio.h>
#include <math.h>

/* EXTERNAL LIBRARIES */
/* TODO: refactor so that SDL is not included here. */
#define SDL_MAIN_HANDLED
#include <SDL2/SDL.h>

/* FEMTOBOX INCLUDES */
#include "pixel.h"
#include "window.h"

#define UNUSED_PARAMETER(x) ((void)(x))
#define INTERNAL_WIDTH  256
#define INTERNAL_HEIGHT 256

int main(int argc, char* argv[])
{
  UNUSED_PARAMETER(argc);
  UNUSED_PARAMETER(argv);

  SDL_Event event;
  window_t* win = window_alloc(INTERNAL_WIDTH, INTERNAL_HEIGHT);

  pixelbuffer_t* pix_buf = pixelbuffer_alloc(INTERNAL_WIDTH, INTERNAL_HEIGHT);

  window_attach_pixelbuffer(win, pix_buf);
  
  while(1)
  {
    if (SDL_PollEvent(&event))
    {
      if (event.type == SDL_QUIT)
      {
        break;
      }
    }

    //uint32_t ticks = SDL_GetTicks();
    for (size_t i = 0; i < pixelbuffer_width(pix_buf); ++i)
    {
      for (size_t j = 0; j < pixelbuffer_height(pix_buf); ++j)
      {
        pixel_t new_pixel;
        if (j == 0 || j == 16)
        {
          pixel_set(&new_pixel, 0, 128, 0);
        }
        else
        {
          //pixel_set(&new_pixel, i * 255 / INTERNAL_HEIGHT, j * 255 / INTERNAL_HEIGHT, (uint8_t)(INTERNAL_HEIGHT / 2 * (1.f + sin((double)ticks / 500)))* 255 / INTERNAL_HEIGHT);
          pixel_set(&new_pixel, 255, 128, 255);
        }
        
        pixelbuffer_set(pix_buf, i, j, new_pixel);
      }
    }

    window_update(win);
    SDL_Delay(16);
  }

  pixelbuffer_free(&pix_buf);
  window_free(&win);
  return 0;
}
