#include "time.h"

void initializeTick(Tick *tick){
    tick->b = SDL_GetTicks();
    tick->a = 0;
    tick->t = 0;
}

int counter(Tick *tick, Uint32 time_elapsed){
    tick->a = SDL_GetTicks();
    Uint32 elapsed_time = tick->a - tick->b;
    if(elapsed_time >= time_elapsed){
        tick->b = SDL_GetTicks();
        return 1;
    }
    return 0;
}

void count_time(Tick *tick){
    tick->a = SDL_GetTicks();
    tick->t = tick->a - tick->b;
    tick->b = SDL_GetTicks();
}