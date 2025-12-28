#include "../includes/button.h"
#include <stdlib.h>

int push_button(BufferButton *buffer, Button *button){
   if(buffer->counter < buffer->size){
    buffer->button[buffer->counter] = button;
    buffer->counter += 1;
    return 0;
   }else if(buffer->counter >= buffer->size){
    buffer->counter = -1;
    return 1;
   }
}

void init_bufferButton(BufferButton *buttons, int size){
    buttons->size = size;
    buttons->counter = 0;
    buttons->button = malloc(sizeof(Button *) * size);
    if(buttons->button == NULL){
        buttons->size = 0;
    }
}

void destroy_bufferButton(BufferButton *buttons){
    if(buttons->button != NULL){
        free(buttons->button);
        buttons->button = NULL;
    }
    buttons->size = 0;
}

void init_button(Button *button){
    SDL_Rect rect = {0,0,0,0};
    button->text = NULL;
    button->rect = rect;
    button->color = get_color(WHITE);
    button->textColor = get_color(BLACK);
    button->click = SDL_FALSE;
    button->hover = SDL_FALSE;
    button->isFill = SDL_TRUE;
    button->isActive = SDL_TRUE;
}

void draw_button(SDL_Renderer *renderer, Button *button){
    SDL_SetRenderDrawColor(renderer,button->color.r,button->color.g,button->color.b,button->color.a);
    if(button->isFill)SDL_RenderFillRect(renderer,&button->rect);
    else{SDL_RenderDrawRect(renderer,&button->rect);}
    if(button->text != NULL)print(renderer,&button->rect,button->textColor,commonPath,button->text);
}

void button_animation(Button *button, Tick *time){
    if(counter(time,500) == 1){
            if(time->t == 0){
                time->t = 1;
                button->textColor = get_color(BLACK);
            }else{
                time->t = 0;
                button->textColor = get_color(WHITE);
            }
        }
}

void button_hover(Button *button){
    if(button->hover) button->textColor = get_color(YELLOW);
}