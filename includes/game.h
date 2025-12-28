#ifndef GAME_H
#define GAME_H

//headers
#include "button.h"

typedef struct game_{
    SDL_bool operations[4];
    Uint8 levels[4];
    Uint8 time;
    Uint8 *dynamic_op;
    Uint8 *op_size;
    SDL_bool isEmpty;
}Game;

typedef struct operations_{
    int first;
    int second;
    Uint8 operation;
    int result;
    SDL_bool success;
}Op;

void choose_operation(Game *game, Button *buttons);

void choose_level(Game *game, BufferButton *buffer);

void pre_init_game(Game *game);

void create_operation(Game *game, Op *operation);

void init_game(Game *game);

void init_operation(Op *op);

void check_game_emptiness(Game *game);

#endif