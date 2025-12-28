#ifndef INPUT_H
#define INPUT_H

#include "button.h"
#include "update.h"

SDL_Point getMousePos(SDL_Event event);

void mouse(Button *button, SDL_Event event);

void keyDown(char **answer, SCENE *scene, SDL_Event event);

#endif