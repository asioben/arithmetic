#include "../includes/input.h"

SDL_Point getMousePos(SDL_Event event){
    //simple function to get mouse position from event
    SDL_Point mouse;

    mouse.x = event.motion.x;
    mouse.y = event.motion.y;

    return mouse;
}

void mouse(Button *button, SDL_Event event){
    //get mouse position
    SDL_Point mouse = getMousePos(event);

    //hover logic
    button->hover = SDL_FALSE;

    //check if you click on a button
    if(SDL_PointInRect(&mouse,&button->rect) == SDL_TRUE && button->isActive == SDL_TRUE){
        if(event.type == SDL_MOUSEBUTTONDOWN) button->click = SDL_TRUE;
        button->hover = SDL_TRUE;
    }
}

void keyDown(char **answer, SCENE *scene ,SDL_Event event){
    if(event.type == SDL_KEYDOWN){
        switch(event.key.keysym.sym){
            case SDLK_0: *answer = push_back_string(*answer,'0');break;
            case SDLK_1: *answer = push_back_string(*answer,'1');break;
            case SDLK_2: *answer = push_back_string(*answer,'2');break;
            case SDLK_3: *answer = push_back_string(*answer,'3');break;
            case SDLK_4: *answer = push_back_string(*answer,'4');break;
            case SDLK_5: *answer = push_back_string(*answer,'5');break;
            case SDLK_6: *answer = push_back_string(*answer,'6');break;
            case SDLK_7: *answer = push_back_string(*answer,'7');break;
            case SDLK_8: *answer = push_back_string(*answer,'8');break;
            case SDLK_9: *answer = push_back_string(*answer,'9');break;
            case SDLK_KP_0: *answer = push_back_string(*answer,'0');break;
            case SDLK_KP_1: *answer = push_back_string(*answer,'1');break;
            case SDLK_KP_2: *answer = push_back_string(*answer,'2');break;
            case SDLK_KP_3: *answer = push_back_string(*answer,'3');break;
            case SDLK_KP_4: *answer = push_back_string(*answer,'4');break;
            case SDLK_KP_5: *answer = push_back_string(*answer,'5');break;
            case SDLK_KP_6: *answer = push_back_string(*answer,'6');break;
            case SDLK_KP_7: *answer = push_back_string(*answer,'7');break;
            case SDLK_KP_8: *answer = push_back_string(*answer,'8');break;
            case SDLK_KP_9: *answer = push_back_string(*answer,'9');break;
            case SDLK_BACKSPACE: *answer = remove_back_string(*answer);break;
            case SDLK_ESCAPE: *scene = START;
        }
    }
}