#include "femtobox/engine/window.h" /* Declarations. */

#include <stdio.h>
#include <string.h>

#define SDL_MAIN_HANDLED
#include <SDL2/SDL.h>

#include "femtobox/engine/pixelbuffer.h"

/* Version string loaded at compile time. */
extern char _binary_data_version_start[];

struct window
{
  SDL_Window* window_;
  SDL_Renderer* renderer_;
  SDL_Texture* framebuffer_;
  pixelbuffer_t* pixelbuffer_;
};

window_t* window_alloc(size_t width, size_t height)
{
  window_t* this = calloc(1, sizeof(window_t));

  if (SDL_Init(SDL_INIT_VIDEO) < 0)
  {
    printf("SDL_Init failed: %s\n", SDL_GetError());
    exit(-1);
  }

  char* name = "Femtobox ";
  char version[32];
  memset(version, 0, 32);
  strcpy(version, name);
  strncpy(version + strlen(name), _binary_data_version_start, 32 - strlen(name));

  this->window_ = SDL_CreateWindow(version, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, SDL_WINDOW_SHOWN);
  if (!this->window_)
  {
    printf("SDL_CreateWindow failed: %s\n", SDL_GetError());
    exit(-1);
  }
  this->renderer_ = SDL_CreateRenderer(this->window_, -1, 0);
  if (!this->renderer_)
  {
    printf("SDL_CreateRenderer failed: %s\n", SDL_GetError());
    exit(-1);
  }
  this->framebuffer_ = NULL;

  return this;
}

void window_free(window_t** p_this)
{
  SDL_DestroyWindow((*p_this)->window_);
  SDL_DestroyRenderer((*p_this)->renderer_);
  SDL_DestroyTexture((*p_this)->framebuffer_);
  //Quit SDL subsystems
  SDL_Quit();

  free(*p_this);
  *p_this = NULL;
}

void window_attach_pixelbuffer(window_t* this, pixelbuffer_t* pixelbuffer)
{
  this->pixelbuffer_ = pixelbuffer;

  if (this->framebuffer_)
  {
    SDL_DestroyTexture(this->framebuffer_);
  }
  this->framebuffer_ = SDL_CreateTexture(this->renderer_, SDL_PIXELFORMAT_RGB24, SDL_TEXTUREACCESS_STREAMING, pixelbuffer_width(this->pixelbuffer_), pixelbuffer_height(this->pixelbuffer_));
  if (!this->framebuffer_)
  {
    printf("SDL_CreateTexture failed: %s\n", SDL_GetError());
    exit(-1);
  }
}

void window_update(window_t* this)
{
  SDL_UpdateTexture(this->framebuffer_, NULL, pixelbuffer_data(this->pixelbuffer_), pixelbuffer_width(this->pixelbuffer_) * sizeof(pixel_t));
  SDL_RenderClear(this->renderer_);
  SDL_RenderCopy(this->renderer_, this->framebuffer_, NULL, NULL);
  SDL_RenderPresent(this->renderer_);
}
