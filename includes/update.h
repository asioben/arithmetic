#ifndef UPDATE_H
#define UPDATE_H

//headers
#include "game.h"

typedef enum SCENE_{
    START,
    GAME,
    SCORE
}SCENE;

void update(SDL_Renderer *renderer, BufferButton *buttons, SCENE *scene, Op *op, Tick *timer, char *answer, int score);

#endif