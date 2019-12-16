#pragma once

/* STANDARD LIBRARIES */
#include <stdbool.h> /* bool type */

typedef struct input input_t;

input_t* input_alloc();

void input_free(input_t**);

void input_poll(input_t*);

bool input_quit(input_t*);

bool input_pushed(input_t*, char key);

bool input_released(input_t*, char key);

bool input_held(input_t*, char key);
