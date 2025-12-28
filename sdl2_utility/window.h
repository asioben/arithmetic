#ifndef WINDOW_H
#define WINDOW_H

#define SDL_MAIN_HANDLED
#include <SDL2/SDL.h>
void init_SDL2Window(SDL_Window **window, SDL_Renderer **renderer, int width, int height);

void quit_SDL2Window(SDL_Window *window, SDL_Renderer *renderer);

#endif