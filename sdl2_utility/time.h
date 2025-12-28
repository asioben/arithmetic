#ifndef TIME_H
#define TIME_H

#define SDL_MAIN_HANDLED
#include <SDL2/SDL.h>

typedef struct tick_{
    Uint32 b;
    Uint32 a;
    Uint32 t;
}Tick;

typedef struct vector_tick{
    Tick xt;
    Tick yt;
}Tick2D;

void initializeTick(Tick *tick);

int counter(Tick *tick, Uint32 time_elapsed);

void count_time(Tick *tick);

#endif