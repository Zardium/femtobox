#pragma once

#include <stdint.h>

#pragma pack(1)
typedef struct pixel
{
  uint8_t r_, g_, b_;
} pixel_t;
#pragma pack()

void pixel_set(pixel_t* pixel, uint8_t r, uint8_t g, uint8_t b);
