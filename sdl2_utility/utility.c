#include <stdio.h>
#include "utility.h"
#include <stdlib.h>

void safe_exit(char *error, SDL_Window *window, SDL_Renderer *renderer){
    printf("%s: %s\n",error, SDL_GetError());
    if(renderer != NULL) SDL_DestroyRenderer(renderer);
    if(window != NULL) SDL_DestroyWindow(window);
    SDL_Quit();
}

int in_string(char *string, char x){
    for(int i = 0; i < sizeof(string)/sizeof(x); i++){
        if(string[i] == x) return 1;
    }
    return 0;
}

SDL_Color get_color(Colors color){
    SDL_Color colour = {0,0,0,255};
    switch(color){
        case RED:
         colour.r = 255;
         return colour;
        case GREEN:
         colour.g = 255;
         return colour;
        case BLUE:
         colour.b = 255;
         return colour;
        case YELLOW:
         colour.r = 255;
         colour.g = 255;
         return colour;
        case ORANGE:
         colour.r = 255;
         colour.g = 165;
         return colour;
        case WHITE:
         colour.r = 255;
         colour.g = 255;
         colour.b = 255;
         return colour;
        case GRAY:
         colour.r = 200;
         colour.g = 200;
         colour.b = 200;
        case BLACK:
         return colour;
    }
}
    
char *int_to_string(int number){
    int nega = 0;
    if(number <= 0){
        if(number == 0) return "0";
        nega = 1;
        number *= -1;
    };

    int elements = SDL_floor(SDL_log10(number)) + 1;
    char *string = malloc(sizeof(char)*(elements+1+nega));
    int j = elements-1;
    int k = 0;

    string[0] = '-';
    for(int i = nega; i < elements+nega; i++){
        k = number/SDL_pow(10,j);
        string[i] = k + '0';
        number = number - (k*(SDL_pow(10,j)));
        j -= 1;
    }

    string[elements + nega] = '\0';
    return string;
}

int in(int *array, int x){
    for(int i = 0; i < sizeof(array)/sizeof(int); i++){
        if(x == array[i]){
            return 1;
        }
    }
    return 0;
}

int string_length(char *string){
    int iteration = 0;

    while(string[iteration] != '\0'){
        iteration += 1;
    }

    return iteration + 1;
}

char *string_concatenate(char *stringA, char *stringB){
    int length[3];

    length[0] = string_length(stringA) - 1;
    length[1] = string_length(stringB);
    length[2] = length[0] + length[1];

    char *string = malloc(length[2]*sizeof(char));

    for(int i = 0; i < length[0]; i++){
        string[i] = stringA[i];
    }

    for(int j = length[0],k = 0; k < length[1]; j++, k++){
        string[j] = stringB[k];
    }

    string[length[2] - 1] = '\0';

    return string;

}

char *reverse_string(char *string){
    int size = string_length(string);
    char *result = malloc(sizeof(char) * size);

    for(int i = 0, j = size-2; i < size-1; i++, j--){
        result[i] = string[j];
    }

    result[size-1] = '\0';

    return result;
}

char *push_back_string(char *string, char character){
    char *result;
    if(string == NULL){
        result = malloc(2 *sizeof(char));
        result[0] = character;
        result[1] = '\0';
    }else{
        char *char_ = malloc(2 * sizeof(char));
        char_[0] = character;
        char_[1] = '\0';
        result = string_concatenate(string,char_);
        free(char_);
    }
    return result;
}

char *remove_back_string(char *string){
    if(string == NULL) return NULL;
    int size = string_length(string);
    if(size <= 1) return NULL;
    char *result = malloc((size-1) * sizeof(char));

    for(int i = 0; i < (size - 2); i++){
        result[i] = string[i];
    }
    result[size-2] = '\0';

    return result;
}

int string_to_int(char *string){
    if(string == NULL) return 0;
    int size = string_length(string);
    int result = 0;
    for(int i = 0; i < size - 1; i++){
        result += SDL_pow(10,(size - i - 2)) * (string[i] - '0');
    }
    return result;
}

int random(int min, int max){
    int result,low,high = 0;

    if(min > max){
        low = max + 1;
        high = min;
    }else{
        low = min;
        high = max + 1;
    }

    result = (rand() % (high - low)) + low;

    return result;
}

int length_to_print(char *string, int policy){
    if(string == NULL) return 0;
    int size = string_length(string);
    return (policy/25) * size * 6;
}

int copy_rect(SDL_Rect *rectA, SDL_Rect *rectB){
    //if(SDL_RectEmpty(rectA) || SDL_RectEmpty(rectB)) return 0;

    rectA->x = rectB->x;
    rectA->y = rectB->y;
    rectA->w = rectB->w;
    rectA->h = rectB->h;

    return 1;
}

int collision(SDL_Rect *rectA, SDL_Rect *rectB){
  if(rectA->x + rectA->w >= rectB->x && rectB->x + rectB->w >= rectA->x && rectA->y + rectA->h >= rectB->y && rectB->y + rectB->h >= rectA->y) return 1;
  else return 0;
}