#ifndef SCENE_H
#define SCENE_H

//headers
#include "../sdl2_utility/utility.h"
#include "../sdl2_utility/texture.h"
#include "../sdl2_utility/time.h"

#define commonPath "C:\\Users\\beni\\OneDrive\\Documents\\arithmetic\\fonts\\round.ttf"

typedef struct button_{
    char *text;
    SDL_Rect rect;
    SDL_Color color;
    SDL_Color textColor;
    SDL_bool click;
    SDL_bool hover;
    SDL_bool isFill; 
    SDL_bool isActive;
}Button;

typedef struct buffer_button{
    Button **button;
    Uint32 size;
    int counter;
}BufferButton;

void init_button(Button *button);

void draw_button(SDL_Renderer *renderer, Button *button);

void button_animation(Button *button, Tick *time);

void button_hover(Button *button);

void init_bufferButton(BufferButton *buttons, int size);

void destroy_bufferButton(BufferButton *buttons);

int push_button(BufferButton *buffer, Button *button);

#endif