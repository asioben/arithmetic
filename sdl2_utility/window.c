#define SDL_MAIN_HANDLED
#include <SDL2/SDL.h>

#include "utility.h"

void init_SDL2Window(SDL_Window **window, SDL_Renderer **renderer, int width, int height){
    if(SDL_Init(SDL_INIT_EVERYTHING) != 0)
     safe_exit("Error of initializing SDL2",*window,*renderer);

    if(SDL_CreateWindowAndRenderer(width,height,0,window,renderer))
     safe_exit("Error to charge window and renderer",*window,*renderer);

}

void quit_SDL2Window(SDL_Window *window, SDL_Renderer *renderer){
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}