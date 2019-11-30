#pragma once

#include <stdlib.h> /* size_t */

#include "pixel.h"  /* pixel_t */

typedef struct pixelbuffer pixelbuffer_t;

pixelbuffer_t* pixelbuffer_alloc(size_t width, size_t height);

void pixelbuffer_free(pixelbuffer_t**);

void pixelbuffer_clear(pixelbuffer_t*, pixel_t clear_color);

void pixelbuffer_set(pixelbuffer_t*, size_t x, size_t y, pixel_t color);

pixel_t pixelbuffer_get(pixelbuffer_t const*, size_t x, size_t y);

size_t pixelbuffer_width(pixelbuffer_t const*);

size_t pixelbuffer_height(pixelbuffer_t const*);

pixel_t const* pixelbuffer_data(pixelbuffer_t const*);
