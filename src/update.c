#include "../includes/update.h"

//function prototype
void start_scene(SDL_Renderer *renderer, BufferButton *buttons);
SCENE game_scene(SDL_Renderer *renderer, Op *op, Tick *timer, char* answer, int score);
void score_scene(SDL_Renderer *renderer, BufferButton *buffer, int score);
void scene_management(SCENE *scene, SDL_Renderer *renderer, BufferButton *buttons, Op *op, Tick *timer, char* answer, int score);

void update(SDL_Renderer *renderer, BufferButton *buttons, SCENE *scene, Op *op, Tick *timer, char* answer, int score){
    //color the background yellow
    SDL_Color background = get_color(YELLOW);
    SDL_SetRenderDrawColor(renderer,background.r,background.g,background.b,background.a);
    SDL_RenderClear(renderer);

    //scene management
    scene_management(scene,renderer,buttons,op,timer,answer,score);

    SDL_RenderPresent(renderer);
}

void scene_management(SCENE *scene, SDL_Renderer *renderer, BufferButton *buttons, Op *op, Tick *timer, char* answer, int score){
    switch(*scene){
        case START: start_scene(renderer,buttons);break;
        case GAME: *scene = game_scene(renderer,op,timer,answer,score);break;
        case SCORE: score_scene(renderer,buttons,score);break;
    }
}

void start_scene(SDL_Renderer *renderer, BufferButton *buttons){
    SDL_Rect big_rect = {50,0,500,750};
    char *texts[13] = {
        {"Arithmetic Game"},
        {"The goal is to quickly answer correctly the most operations you can. "},
        {"You can choose the operation, the level and the time pressure."},
        {"Escape to quit"},
        {"Addition"},
        {"Level (range): "},
        {"Soustraction"},
        {"Level (range): "},
        {"Multiplication"},
        {"Level (range): "},
        {"Division"},
        {"Level (range): "},
        {"Time : "}
    };

     SDL_Rect textRects[13] = {
        {75,25,length_to_print(texts[0],50),50},
        {75,100,length_to_print(texts[1],25),25},
        {75,135,length_to_print(texts[2],25),25},
        {75,170,length_to_print(texts[3],25),25},
        {125,205,length_to_print(texts[4],25),25},
        {150,240,length_to_print(texts[5],25),25},
        {125,290,length_to_print(texts[6],25),25},
        {150,325,length_to_print(texts[7],25),25},
        {125,375,length_to_print(texts[8],25),25},
        {150,410,length_to_print(texts[9],25),25},
        {125,460,length_to_print(texts[10],25),25},
        {150,495,length_to_print(texts[11],25),25},
        {100,545,length_to_print(texts[12],25),25}
    };

    SDL_SetRenderDrawColor(renderer,200,200,200,0);
    SDL_RenderFillRect(renderer,&big_rect);

    for(int i = 0; i < 13; i++) print(renderer,&textRects[i],get_color(BLACK),commonPath,texts[i]);

    for(int i = 0; i < 23; i++)draw_button(renderer,buttons->button[i]);
}

SCENE game_scene(SDL_Renderer *renderer, Op *op, Tick *timer, char* answer, int score){
    //check time
    if(counter(timer,1000) == 1){
        if(timer->t == 0) {
            op->success = SDL_TRUE;
            return SCORE;
        }
        timer->t -= 1;
    }

    //choose the right string for operation
    char *operation;
    switch(op->operation){
        case 0: operation = " + ";break;
        case 1: operation = " - ";break;
        case 2: operation = " * ";break;
        case 3: operation = " / ";break;
    }

    //operation and answer text
    char *first_ = string_concatenate(int_to_string(op->first),operation);
    char *second_ = string_concatenate(first_,int_to_string(op->second));
    char *text = string_concatenate(second_," =");
    //char *_answer = "enc";
    //if(answer != NULL)_answer = reverse_string(answer);

    //time text
    char *time_left = string_concatenate("Time left: ",int_to_string(timer->t));

    //score text
    char *ur_score = string_concatenate("Your score: ", int_to_string(score));
    int length_score = length_to_print(ur_score,25);

    //set rect for print 
    SDL_Rect op_rect = {0,250,600,100};
    SDL_Rect op_ = {250,287,length_to_print(text,25),25};
    SDL_Rect answer_ = {275,600,length_to_print(answer,50),25};
    SDL_Rect time_ = {0,0,length_to_print(time_left,25),25};
    SDL_Rect score_ = {600 - length_score,0,length_score,25};

    //operation and answer box
    SDL_SetRenderDrawColor(renderer,200,200,200,0);
    SDL_RenderFillRect(renderer,&op_rect);
    SDL_SetRenderDrawColor(renderer,255,255,0,0);
    if(answer != NULL)SDL_RenderFillRect(renderer,&answer_);

    //print the operations and the answer
    print(renderer,&op_,get_color(BLACK),commonPath,text);
    if(answer != NULL)print(renderer,&answer_,get_color(BLACK),commonPath,answer);
    print(renderer,&time_,get_color(BLACK),commonPath,time_left);
    print(renderer,&score_,get_color(BLACK),commonPath,ur_score);

    if(string_to_int(answer) == op->result) op->success= SDL_FALSE;

    //free the allocate memory (string)
    free(first_);
    free(second_);
    free(text);
    free(time_left);
    free(ur_score);

    return GAME;
}

void score_scene(SDL_Renderer *renderer, BufferButton *buffer, int score){
    char *score_text = string_concatenate("Your score is: ", int_to_string(score));
    int score_length = length_to_print(score_text,25);
    SDL_Rect score_rect = {300-(score_length/2),250,score_length,25};

    if(!buffer->button[23]->isActive) buffer->button[23]->isActive = SDL_TRUE;
    if(!buffer->button[24]->isActive) buffer->button[24]->isActive = SDL_TRUE;
    if(buffer->button[23]->hover) buffer->button[23]->color = get_color(WHITE);
    else{buffer->button[23]->color = get_color(GRAY);}
    if(buffer->button[24]->hover) buffer->button[24]->textColor = get_color(BLACK);
    else{buffer->button[24]->textColor = get_color(WHITE);}

    for(int i = 23; i < 25; i++) draw_button(renderer,buffer->button[i]);

    print(renderer,&score_rect,get_color(BLACK),commonPath,score_text);
}