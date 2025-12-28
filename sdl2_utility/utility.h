#ifndef UTILITY_H
#define UTILITY_H

#define SDL_MAIN_HANDLED
#include <SDL2/SDL.h>

#define HEIGHT 600
#define WIDTH 800

typedef enum {
    RED,
    GREEN,
    BLUE,
    YELLOW,
    ORANGE,
    WHITE,
    BLACK,
    GRAY
}Colors;

SDL_Color get_color(Colors color);

void safe_exit(char *error, SDL_Window *window, SDL_Renderer *renderer);

int in_string(char *string, char x);

char *int_to_string(int number);

int in(int *array, int x);

int string_length(char *string);

char *push_back_string(char *string, char character);

char *string_concatenate(char *stringA, char *stringB);

char *reverse_string(char *string);

char *remove_back_string(char *string);

int string_to_int(char *string);

int length_to_print(char *string, int policy);

int random(int min, int max);

int copy_rect(SDL_Rect *rectA, SDL_Rect *rectB);

int collision(SDL_Rect *rectA, SDL_Rect *rectB);

#endif