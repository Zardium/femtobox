/* STANDARD LIBRARY */
#include <stdio.h>
#include <math.h>

/* EXTERNAL LIBRARIES */

/* FEMTOBOX INCLUDES */
#include "pixel.h"
#include "window.h"
#include "input.h"
#include "timing.h"

#define UNUSED_PARAMETER(x) ((void)(x))
#define INTERNAL_WIDTH  256
#define INTERNAL_HEIGHT 256

int main(int argc, char* argv[])
{
  UNUSED_PARAMETER(argc);
  UNUSED_PARAMETER(argv);

  window_t* win = window_alloc(512, 512);
  pixelbuffer_t* pix_buf = pixelbuffer_alloc(INTERNAL_WIDTH, INTERNAL_HEIGHT);
  window_attach_pixelbuffer(win, pix_buf);
  
  input_t* in = input_alloc();
  int running = true;
  while(running)
  {
    input_poll(in);
    if (input_quit(in))
    {
      running = false;
      continue;
    }

    size_t ticks = timing_get_ticks();
    for (size_t i = 0; i < pixelbuffer_width(pix_buf); ++i)
    {
      for (size_t j = 0; j < pixelbuffer_height(pix_buf); ++j)
      {
        pixel_t new_pixel;
        if (j % 16 == 0 || i % 16 == 0)
        {
          pixel_set(&new_pixel, 0, 0, 0);
        }
        else
        {
          pixel_set(&new_pixel, i * 255 / INTERNAL_HEIGHT, j * 255 / INTERNAL_HEIGHT, (uint8_t)(INTERNAL_HEIGHT / 2 * (1.f + sin((double)ticks / 500)))* 255 / INTERNAL_HEIGHT);
          //pixel_set(&new_pixel, 255, 128, 255);
        }
        
        pixelbuffer_set(pix_buf, i, j, new_pixel);
      }
    }

    window_update(win);
    timing_delay(16);
  }

  /* Free allocated resources. */
  input_free(&in);

  pixelbuffer_free(&pix_buf);
  window_free(&win);
  return 0;
}
