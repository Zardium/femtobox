#include "femtobox/engine/input.h" /* Declarations. */

/* EXTERNAL LIBRARIES */
#include <SDL2/SDL.h> /* SDL_Event, SDL_PollEvent, SDL_Keycode */

#define MAX_KEY_COUNT 128

struct input
{
  bool quit_;       /* Whether a message to quit was received.     */
  uint8_t* keys_;      /* Handle to the currently active keys.        */
  uint8_t* keys_prev_; /* Handle to the previous frame's active keys. */
  uint8_t key_data1_[MAX_KEY_COUNT]; /* A set of key data. */
  uint8_t key_data2_[MAX_KEY_COUNT]; /* A set of key data. */
  SDL_Event event_;
};

/* Private function declarations. */

static void swap_keys_(input_t*);

static void handle_event_(input_t*);

static bool symbol_in_range_(SDL_Keycode);

/* Public function implementations. */

input_t* input_alloc()
{
  input_t* new_input    = calloc(1, sizeof(input_t));
  new_input->keys_      = new_input->key_data1_;
  new_input->keys_prev_ = new_input->key_data2_;
  return new_input;
}

void input_free(input_t** p_this)
{
  free(*p_this);
  *p_this = NULL;
}

void input_poll(input_t* this)
{
  swap_keys_(this);
  while (SDL_PollEvent(&this->event_))
  {
    handle_event_(this);
  }
}

bool input_quit(input_t* this)
{
  return this->quit_;
}

bool input_pushed(input_t* this, char key)
{
  uint16_t key_u = key;
  return symbol_in_range_(key_u) &&
         this->keys_[key_u] == SDL_PRESSED &&
         this->keys_prev_[key_u] == SDL_RELEASED;
}

bool input_released(input_t* this, char key)
{
  uint16_t key_u = key;
  return symbol_in_range_(key_u) &&
         this->keys_[key_u] == SDL_RELEASED &&
         this->keys_prev_[key_u] == SDL_PRESSED;
}

bool input_held(input_t* this, char key)
{
  uint16_t key_u = key;
  return symbol_in_range_(key_u) &&
         this->keys_[key_u] == SDL_PRESSED &&
         this->keys_prev_[key_u] == SDL_PRESSED;
}

/* Private function implementations. */

void swap_keys_(input_t* this)
{
  /* Swap handles to key data arrays. */
  uint8_t* temp = this->keys_prev_;
  this->keys_prev_ = this->keys_;
  this->keys_ = temp;
  /* Zero out the current frame of keys. */
  memset(this->keys_, 0, MAX_KEY_COUNT);
}

void handle_event_(input_t* this)
{
  switch (this->event_.type)
  {
    case SDL_QUIT:
    {
      this->quit_ = true;
      break;
    }
    case SDL_KEYDOWN:
    {
      SDL_Keycode symbol = this->event_.key.keysym.sym;
      if (symbol_in_range_(symbol))
      {
        this->keys_[symbol] = SDL_PRESSED;
      }
      break;
    }
    case SDL_KEYUP:
    {
      SDL_Keycode symbol = this->event_.key.keysym.sym;
      if (symbol_in_range_(symbol))
      {
        this->keys_[symbol] = SDL_RELEASED;
      }
      break;
    }
    default:
    {
      break;
    }
  }
}

static bool symbol_in_range_(int symbol)
{
  return symbol >= 0 && symbol < MAX_KEY_COUNT;
}
