#include <stdio.h>
#include <SDL2/SDL.h>

#define UNUSED_PARAMETER(x) ((void)(x))
#define INTERNAL_WIDTH  256
#define INTERNAL_HEIGHT 256

#pragma pack(1)
typedef struct pixel
{
  uint8_t r, g, b;
} pixel;

void pixel_set(pixel* pixel, uint8_t r, uint8_t g, uint8_t b)
{
  pixel->r = r;
  pixel->g = g;
  pixel->b = b;
}

int main(int argc, char* argv[])
{
  UNUSED_PARAMETER(argc);
  UNUSED_PARAMETER(argv);

  SDL_Event event;
  SDL_Window* window = NULL;
  SDL_Renderer* renderer = NULL;
  SDL_Texture* framebuffer = NULL;
  pixel* pixels = malloc(sizeof(pixel) * INTERNAL_WIDTH * INTERNAL_HEIGHT);

  for (int i = 0; i < INTERNAL_WIDTH; ++i)
  {
    for (int j = 0; j < INTERNAL_HEIGHT; ++j)
    {
      pixel new_pixel = {i * 255 / INTERNAL_WIDTH, j * 255 / INTERNAL_HEIGHT, 0};
      pixels[i + (j * INTERNAL_WIDTH)] = new_pixel;
    }
  }

  SDL_Init(SDL_INIT_VIDEO);
  window = SDL_CreateWindow("Femtobox v0", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 512, 512, SDL_WINDOW_SHOWN);
  renderer = SDL_CreateRenderer(window, -1, 0);
  framebuffer = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGB24, SDL_TEXTUREACCESS_STREAMING, INTERNAL_WIDTH, INTERNAL_HEIGHT);

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
     for (int i = 0; i < INTERNAL_WIDTH; ++i)
     {
       for (int j = 0; j < INTERNAL_HEIGHT; ++j)
       {
         pixel new_pixel;
         if (j == 0 || j == 16)
         {
           pixel_set(&new_pixel, 0, 0, 0);
         }
         else
         {
           //pixel_set(&new_pixel, i * 255 / INTERNAL_HEIGHT, j * 255 / INTERNAL_HEIGHT, (uint8_t)(INTERNAL_HEIGHT / 2 * (1.f + sin((double)ticks / 500)))* 255 / INTERNAL_HEIGHT);
           pixel_set(&new_pixel, 255, 255, 255);
         }
         
         pixels[i + (j * INTERNAL_WIDTH)] = new_pixel;
       }
     }

    SDL_UpdateTexture(framebuffer , NULL, pixels, INTERNAL_WIDTH * sizeof(pixel));
    SDL_RenderClear(renderer);
    SDL_RenderCopy(renderer, framebuffer , NULL, NULL);
    SDL_RenderPresent(renderer);
    SDL_Delay(16);
  }

  free(pixels);

  SDL_DestroyTexture(framebuffer);
  //Destroy window
  SDL_DestroyWindow( window );
  //Quit SDL subsystems
  SDL_Quit();
  return 0;
}
