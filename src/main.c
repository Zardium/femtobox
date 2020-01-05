/* STANDARD LIBRARY */
#include <stdio.h>  /* fread  */
#include <math.h>   /* sin    */
#include <string.h> /* strcmp */

/* EXTERNAL LIBRARIES */

/* FEMTOBOX INCLUDES */
  /* ENGINE INCLUDES */
  #include "femtobox/engine/pixel.h"
  #include "femtobox/engine/window.h"
  #include "femtobox/engine/input.h"
  #include "femtobox/engine/timing.h"
  /* FE INCLUDES */
  #include "femtobox/fe/lexer.h"
  #include "femtobox/fe/instruction.h"
  #include "femtobox/fe/interpreter.h"

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
  
  for (size_t i = 0; i < pixelbuffer_width(pix_buf); ++i)
  {
    for (size_t j = 0; j < pixelbuffer_height(pix_buf); ++j)
    {
      pixel_t new_pixel;
      // if (j % 16 == 0 || i % 16 == 0)
      // {
        pixel_set(&new_pixel, 0, 0, 0);
      // }
      // else
      // {
      //   pixel_set(&new_pixel, i * 255 / INTERNAL_HEIGHT, j * 255 / INTERNAL_HEIGHT, (uint8_t)(INTERNAL_HEIGHT / 2 * (1.f + sin((double)ticks / 500)))* 255 / INTERNAL_HEIGHT);
      //   //pixel_set(&new_pixel, 255, 128, 255);
      // }
      
      pixelbuffer_set(pix_buf, i, j, new_pixel);
    }
  }

  window_update(win);
  window_show(win);

  input_t* in = input_alloc();

  char in_buffer[32];

  memset(in_buffer, 0, 32);
  fgets(in_buffer, 32, stdin);

  token_t* t = lexer_tokenize(in_buffer);
  token_print_list(t);

  int running = true;
  while (running)
  {
    input_poll(in);
    if (input_quit(in))
    {
      running = false;
      continue;
    }

    // size_t ticks = timing_get_ticks();

    window_update(win);
    timing_delay(16);
  }

  /* Free allocated resources. */
  input_free(&in);

  pixelbuffer_free(&pix_buf);
  window_free(&win);
  return 0;
}
