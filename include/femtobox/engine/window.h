#pragma once

#include <stdint.h> /* size_t */

#include "pixelbuffer.h"

/* Forward declare an opaque window manager. */
typedef struct window window_t;

window_t* window_alloc(size_t width, size_t height);

void window_free(window_t**);

void window_attach_pixelbuffer(window_t*, pixelbuffer_t*);

void window_update(window_t*);
