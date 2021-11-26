#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

int relation_to_index(FILE *file){

    bool first_word_loaded = false;
    bool second_word_loaded = false;

    char temp[31];
    int index = 0;

    char character = 'd';

    // char univerzum[4][4] = {{A},{B},{C},{D}};

    while(character != '\n' && character != EOF){
        character = getc(file);
        if(character == '('){
            while(character != ' '){
                //load to temp
                character = getc(file);
                temp[index++] = character;

                if (character == ' '){
                    temp[index-1] = '\0';
                    printf("first word %s\n", temp);
                    // printf("finding 1st index\n");
                    index = 0;
                    strcpy(temp,"");
                    first_word_loaded = true;
                    continue;
                }
                // printf("first_word: %c\n", character);
            }
            while(character != ')'){
                character = getc(file);
                temp[index++] = character;

                if( character == ')'){
                    temp[index-1] = '\0';
                    printf("second word %s\n", temp);
                    // printf("finding 2nd index\n");
                    index = 0;
                    strcpy(temp,"");
                    second_word_loaded = true;
                    continue;
                }
                // printf("second_word: %c\n", character);
            }
            if(second_word_loaded && first_word_loaded){
                printf("incrementing index of the array of pairs\n");
                first_word_loaded = false;
                second_word_loaded = false;
            }
        }
    }

    return 0;
}


int main(int argc, char * argv[]){
    FILE *file;
    printf("params %d %s\n", argc, argv[0]);

    char *filename = argv[1];
    file = fopen(filename, "r");

    if(file == NULL){
        fprintf(stderr,"This file name is invalid.");
        fclose(file);
        return -1;
    }

    relation_to_index(file);

    fclose(file);
    return 0;
}