#include <stdio.h>
#include <stdlib.h>
#include <math.h>

char *reverse(char *string);
char *string_concatenate(char *stringA, char *stringB);
int string_length(char *string);
char *push_back_string(char *string, char character);
char *remove_back_string(char *string);
int string_to_int(char *string);

char *reverse(char *string){
    int size = string_length(string);
    char *result = malloc(sizeof(char) * size);

    for(int i = 0, j = size-2; i < size-1; i++, j--){
        result[i] = string[j];
    }

    result[size-1] = '\0';

    return result;
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

int string_length(char *string){
    int iteration = 0;

    while(string[iteration] != '\0'){
        iteration += 1;
    }

    return iteration + 1;
}

char *push_back_string(char *string, char character){
    char *result;
    if(string == ((void *) 0)){
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
        result += pow(10,(size - i - 2)) * (string[i] - '0');
    }
    return result;
}

int main(){
    char *string = "7829";
    printf("C'est %i !",string_to_int(string));

    return 0;
}