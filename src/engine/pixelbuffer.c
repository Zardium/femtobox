#include "femtobox/engine/pixelbuffer.h" /* Declarations. */

/* STANDARD LIBRARY */
#include <stdlib.h> /* malloc, calloc */

struct pixelbuffer
{
  size_t width_;
  size_t height_;
  pixel_t* pixels_;
};

pixelbuffer_t* pixelbuffer_alloc(size_t width, size_t height)
{
  pixelbuffer_t* this = malloc(sizeof(pixelbuffer_t));
  this->width_ = width;
  this->height_ = height;
  this->pixels_ = calloc(width * height, sizeof(pixel_t));
  return this;
}

void pixelbuffer_free(pixelbuffer_t** p_this)
{
  free((*p_this)->pixels_);
  free(*p_this);
  *p_this = NULL;
}

void pixelbuffer_clear(pixelbuffer_t* this, pixel_t clear_color)
{
  for (size_t i = 0; i < this->width_; ++i)
  {
    for (size_t j = 0; j < this->height_; ++j)
    {
      this->pixels_[i + (j * this->height_)] = clear_color;
    }
  }
}

void pixelbuffer_set(pixelbuffer_t* this, size_t x, size_t y, pixel_t color)
{
  this->pixels_[x + (y * this->height_)] = color;
}

pixel_t pixelbuffer_get(pixelbuffer_t const* this, size_t x, size_t y)
{
  return this->pixels_[x + (y * this->height_)];
}

size_t pixelbuffer_width(pixelbuffer_t const* this)
{
  return this->width_;
}

size_t pixelbuffer_height(pixelbuffer_t const* this)
{
  return this->height_;
}

pixel_t const* pixelbuffer_data(pixelbuffer_t const* this)
{
  return this->pixels_;
}
