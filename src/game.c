#include "../includes/game.h"

//functions prototype
void help_choose_level(Game *game, BufferButton *buffer, int i, int offset, int level);
void operation_layer(Game *game, Op *op);
void level_layer(Game *game, Op *op);

void help_choose_level(Game *game, BufferButton *buffer, int i, int offset, int level){
    if(buffer->button[i]->click){
       if(buffer->button[i]->color.r == 0){
           buffer->button[i]->color = get_color(WHITE);
           buffer->button[i]->textColor = get_color(BLACK);
           game->levels[level] = 0;
        }else{
            buffer->button[game->levels[level] + offset]->color = get_color(WHITE);
            buffer->button[game->levels[level] + offset]->textColor = get_color(BLACK);

            game->levels[level] = i-offset;
            buffer->button[i]->color = get_color(BLUE);
            buffer->button[i]->textColor = get_color(WHITE);
        }
        buffer->button[i]->click = SDL_FALSE;
    }
}

void choose_operation(Game *game, Button *buttons){
    for(int i = 0; i < 4; i++){
            if(buttons[i].click){
    
                if(!game->operations[i]){
                    buttons[i].color = get_color(BLUE);
                    buttons[i].isFill = SDL_TRUE;
                    game->operations[i] = SDL_TRUE;
                }else{
                    buttons[i].color = get_color(BLACK);
                    buttons[i].isFill = SDL_FALSE;
                    game->operations[i] = SDL_FALSE;
                }
                buttons[i].click = SDL_FALSE;
            }
        }
}

void choose_level(Game *game, BufferButton *buffer){
    for(int i = 5; i < 23; i++){
        if(i >= 5 && i < 9) help_choose_level(game,buffer,i,4,0);
        if(i >= 9 && i < 13) help_choose_level(game,buffer,i,8,1);
        if(i >= 13 && i < 16) help_choose_level(game,buffer,i,12,2);
        if(i >= 16 && i < 19) help_choose_level(game,buffer,i,15,3);
        if(i >= 19 && i < 23){
            if(buffer->button[i]->click ){
    
                if(buffer->button[i]->color.r == 0){
                    buffer->button[i]->color = get_color(WHITE);
                    buffer->button[i]->textColor = get_color(BLACK);
                    game->time = 0;
                }else{
                   buffer->button[((game->time)/30) + 18]->color = get_color(WHITE);
                   buffer->button[((game->time)/30) + 18]->textColor = get_color(BLACK);

                   buffer->button[i]->color = get_color(BLUE);
                   buffer->button[i]->textColor = get_color(WHITE);
                   game->time = (i-18) * 30;
                }
                buffer->button[i]->click = SDL_FALSE;
           }
        }
    }
}

void pre_init_game(Game *game){
    for(int i = 0 ; i < 4; i++){
        game->operations[i] = SDL_FALSE;
        game->levels[i] = 0;
    }
    game->dynamic_op = NULL;
    game->time = 0;
    game->isEmpty = SDL_TRUE;
}

void init_game(Game *game){
    int array[4] = {-1,-1,-1,-1};
    int k = 0;
    for(int i = 0; i < 4; i++){
        if(game->operations[i]){
            array[i] = i;
            k += 1;
        }
    }
    game->dynamic_op = malloc(sizeof(Uint8) * k);
    game->op_size = (Uint8)k;
    k = 0;
    for(int j = 0; j < 4; j++){
         if(array[j] != -1){
            game->dynamic_op[k] = array[j];
            k += 1;
         }
    }
    return 0;
}

void check_game_emptiness(Game *game){
   if((game->operations[0] == SDL_FALSE &&
      game->operations[1] == SDL_FALSE &&
      game->operations[2] == SDL_FALSE &&
      game->operations[3] == SDL_FALSE ) ||
     (game->levels[0] == 0 &&
      game->levels[1] == 0 &&
      game->levels[2] == 0 &&
      game->levels[3] == 0 ) ||
      game->time == 0) game->isEmpty = SDL_TRUE;  
   else{game->isEmpty = SDL_FALSE;}
}

void init_operation(Op *op){
    op->first = 0;
    op->second = 0;
    op->operation = 0;
    op->result = 0;
    op->success = SDL_TRUE;
}

void operation_layer(Game *game, Op *op){
    switch(op->operation){
        case 0: op->result = op->first + op->second;break;
        case 1: {
            op->result = op->first + op->second;
            op->first = op->result;
            op->result = op->first - op->second;
        }break;
        case 2: op->result = op->first * op->second;break;
        case 3: {
            op->result = op->first * op->second;
            op->first = op->result;
            op->result = op->first / op->second;
        }break;
    }
}

void level_layer(Game *game, Op *op){
    int level = game->levels[op->operation];

    if(op->operation < 2){
        op->first = random(1,SDL_pow((double)10,(double)level));
        op->second = random(1,SDL_pow((double)10,(double)level));
    }else{
        op->first = random(2,SDL_pow((double)10,(double)(level)));
        op->second = random(2,SDL_pow((double)10,(double)(level)));
    }
}

void create_operation(Game *game, Op *operation){
    operation->operation = game->dynamic_op[random(0,game->op_size-1)];

    level_layer(game,operation);
    operation_layer(game,operation);
}