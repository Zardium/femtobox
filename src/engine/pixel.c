#include "femtobox/engine/pixel.h"

void pixel_set(pixel_t* pixel, uint8_t r, uint8_t g, uint8_t b)
{
  pixel->r_ = r;
  pixel->g_ = g;
  pixel->b_ = b;
}
