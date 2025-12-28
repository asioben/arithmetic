#ifndef TEXTURE_H
#define TEXTURE_H

#include "utility.h"
#include <SDL2_ttf/SDL_ttf.h>

SDL_Texture* loadImg(SDL_Renderer *renderer,char *path);

void renderTexture(SDL_Renderer *renderer, SDL_Texture *texture);

int print(SDL_Renderer *renderer, SDL_Rect *rect, SDL_Color color, const char *path, const char *text);

SDL_Texture *screen_shot(SDL_Renderer *renderer);

#endif
