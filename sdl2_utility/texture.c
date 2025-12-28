#include "texture.h"
#include <SDL2_image/SDL_image.h>
#include <SDL2_ttf/SDL_ttf.h>

SDL_Texture* loadImg(SDL_Renderer *renderer,char *path){
    if(in_string(path,'.') == 0) return NULL;
    SDL_Surface *img = IMG_Load(path);
    SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer,img);
    SDL_FreeSurface(img);
    return texture;
}

void renderTexture(SDL_Renderer *renderer, SDL_Texture *texture){
    SDL_RenderClear(renderer);
    SDL_RenderCopy(renderer,texture,NULL,NULL);
}

int initializeFont(SDL_Surface **surface, SDL_Texture **texture){

}

int print(SDL_Renderer *renderer, SDL_Rect *rect, SDL_Color color, const char *path, const char *text){
    if(TTF_Init() == -1) return 0;
    TTF_Font *font = TTF_OpenFont(path,64);
    if(font == 0) return 0;
    SDL_Surface *surface = TTF_RenderText_Blended(font,text,color);
    SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer,surface);
    SDL_FreeSurface(surface);
    SDL_RenderCopy(renderer,texture,NULL,rect);
    SDL_DestroyTexture(texture);
    TTF_CloseFont(font);
    TTF_Quit();
    //SDL_RenderPresent(renderer);
    return 1;
}

SDL_Texture *screen_shot(SDL_Renderer *renderer){
    SDL_Surface *img = SDL_CreateRGBSurface(0,WIDTH,HEIGHT,32,0,0,0,0);
    /*SDL_RenderReadPixels(renderer,NULL,img->format->format,img->pixels,img->pitch);
    Uint16 *pixels = (Uint16 *) img->pixels; 
    SDL_Color rgba;
    for(int i = 0; i < img->w * img->h; i++){
        SDL_GetRGBA(pixels[i],img->format,&rgba.r,&rgba.g,&rgba.b,&rgba.a);
        pixels[i] = SDL_MapRGBA(img->format,rgba.r,rgba.g,rgba.b,rgba.a+(1/255));
    }*/
    SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer,img);
    SDL_FreeSurface(img);
    return texture;
}