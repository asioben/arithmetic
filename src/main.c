#define SDL_MAIN_HANDLED

//include headers
#include "../includes/update.h"
#include "../includes/input.h"
#include "../includes/game.h"

#define SAFE_RELEASE(x) if(x != NULL) free(x);

void init_level_buttons(Button *level, BufferButton *buffer, int x, int y, int *k, int _, int limit);

void init_level_buttons(Button *level, BufferButton *buffer, int x, int y, int *k, int _, int limit){
    init_button(level);
    SDL_Rect levels = {x + (*k*30),y,20,25};
    level->text = int_to_string((*k + 1)*_);
    level->rect = levels;
    *k += 1;
    if(*k >= limit) *k = 0;
    push_button(buffer,level);
}

int main(){
    //variables
    SDL_Window *window = NULL;
    SDL_Renderer *renderer = NULL;
    SDL_bool loop = SDL_TRUE;
    Button start;
    SDL_Rect start_pos = {175,605,200,100};
    Tick start_;
    SCENE scene = START;
    Button operations[4];
    BufferButton buttons;
    Button addition[4];
    Button soustraction[4];
    Button multiplication[3];
    Button division[3];
    Button timer[4];
    Game game;
    Op op;
    Tick time_pressure;
    char *answer = NULL;
    int score = -1;
    Button restart;
    Button home;

    //init the buffer button
    init_bufferButton(&buttons,25);

    //init the time
    initializeTick(&start_);

    //init button
    init_button(&start);
    start.rect = start_pos;
    start.text = "START";
    start.color = get_color(BLUE);
    start.textColor = get_color(WHITE);
    if(push_button(&buttons,&start) == 1)loop = SDL_FALSE;

    for(int i = 0; i < 4; i++){
        SDL_Rect operations_pos = {75,205 + (i*85),25,25};
        init_button(&operations[i]);
        operations[i].isFill = SDL_FALSE;
        operations[i].color = get_color(BLACK);
        operations[i].rect = operations_pos;
        push_button(&buttons,&operations[i]);
    }
    int k = 0; 
    for(int j = 0; j < 4; j++)init_level_buttons(&addition[j],&buttons,275,240,&k,1,4);
    for(int j = 0; j < 4; j++)init_level_buttons(&soustraction[j],&buttons,275,325,&k,1,4);
    for(int j = 0; j < 3; j++)init_level_buttons(&multiplication[j],&buttons,275,410,&k,1,3);
    for(int j = 0; j < 3; j++)init_level_buttons(&division[j],&buttons,275,495,&k,1,3);
    for(int j = 0; j < 4; j++)init_level_buttons(&timer[j],&buttons,200,545,&k,30,4);

    init_button(&restart);
    init_button(&home);

    SDL_Rect restart_ = {200,400,200,100};
    SDL_Rect home_ = {200,550,200,100};

    restart.rect = restart_;
    restart.text = "RESTART";
    restart.textColor = get_color(BLACK);
    restart.color = get_color(GRAY);
    restart.isActive = SDL_FALSE;

    home.rect = home_;
    home.text = "HOME";
    home.textColor = get_color(WHITE);
    home.color = get_color(BLUE);
    home.isActive = SDL_FALSE;

    push_button(&buttons,&restart);
    push_button(&buttons,&home);

    //init game
    pre_init_game(&game);

    //init the timer
    initializeTick(&time_pressure);

    //init operations
    init_operation(&op);

    //create the window
    init_SDL2Window(&window,&renderer,HEIGHT,WIDTH);

    //loop
    while(loop){
        if(scene == START){
            for(int i = 0; i < 23; i++)buttons.button[i]->isActive = SDL_TRUE;
            score = 0;
            check_game_emptiness(&game);
        }
        if(start.click){
            if(!game.isEmpty){
                scene = GAME;
                init_game(&game);
                op.success = SDL_FALSE;
                time_pressure.t = game.time;
                for(int i = 0; i < 23; i++)buttons.button[i]->isActive = SDL_FALSE;
            }
            start.click = SDL_FALSE;
        }
        SDL_SetWindowTitle(window,"Arithmetic");
        if(scene == START)button_animation(&start,&start_);
        if(scene == START)button_hover(&start);
        if(scene == START)choose_operation(&game,operations);
        if(scene == START)choose_level(&game,&buttons);
        if(!op.success){
            create_operation(&game,&op);
            op.success = SDL_TRUE;
            answer = NULL;
            score += 1;
        }
        if(scene == SCORE){
            if(restart.click){
               scene = GAME;
               restart.click = SDL_FALSE;
               restart.isActive = SDL_FALSE;
               home.isActive = SDL_FALSE;
               op.success = SDL_FALSE;
               time_pressure.t = game.time;
               score = 0;
            }
            if(home.click){
                scene = START;
                home.click = SDL_FALSE;
                restart.isActive = SDL_FALSE;
                home.isActive = SDL_FALSE;
            }
        }
        update(renderer,&buttons,&scene,&op,&time_pressure,answer,score);
        SDL_Event event;
        while(SDL_PollEvent(&event) == 1){
            switch(event.type){
                case SDL_QUIT: loop = SDL_FALSE; break;
                default: {
                    keyDown(&answer,&scene,event);
                    for(int i = 0; i < buttons.size; i++){
                        mouse(buttons.button[i],event);
                    }
                }
            }
        }
    }

    quit_SDL2Window(window,renderer);
    destroy_bufferButton(&buttons);
    SAFE_RELEASE(game.dynamic_op);
    SAFE_RELEASE(answer);

    return 0;
}