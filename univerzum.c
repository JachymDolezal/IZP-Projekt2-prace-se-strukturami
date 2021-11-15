#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

typedef struct {
    //int index;
    char element[31];
} Universum;

typedef struct {
    int set[3];
} Set;


int convert_to_index(FILE *file, Set *s, Universum *u, int uni_element){

    //get element in temp
    //compare with uni
    //if found -> put indx in Set *s
    char temp[31];
    int index = 0;
    int element_index = 0;
    bool was_found = false;

    //TODO udelat separatni funkci
    char character = 'd';
    if (getc(file) != 'S' || getc(file) != ' '){
        fprintf(stderr, "Set not defined");
        return false;
    }

    while(character != '\n' && character != EOF){
        //goes to a new character
        character = getc(file);

        if (character == ' ' || character == '\n' || character == EOF) {
            temp[index+1] = '\0';
            index = 0;
            for (int j = 0; j < uni_element; j++){

                if (strcmp(temp, u[j].element) == 0){
                    s->set[element_index] = j;
                    //expression must have struct or union type but it has type "Set *
                    element_index++;
                    was_found = true;
                    break;
                }
            }
            if (!was_found){
                fprintf(stderr, "Prvek neni z univerza");
                return false;
            }
            //empties a the temp string
            strcpy(temp,"");
            continue;
        }

        temp[index] = character;
        index++;
    }
    return 1;
}
/*
U jablka hrusky tresne jahody broskve maliny\n
S hrusky jablka tresne\n// => [1,0,2]
    1       0       2

*/
//TODO - dat inkrementaci na konec
int universum_check(FILE *file, int *counter, int *line_length, Universum *u){

    int element_len = 0;
    int idx = 0;
    char character = getc(file); //toto prve getc bych tu nechal kdyz budeme zobecnovat pro S R C, aby sme mohli podle prvniho pismena vedeli co s tim radkem delat
    if (character != 'U' || getc(file) != ' '){
        fprintf(stderr, "Universum not defined");
        return -1;
    }

    //loop zacina uz na 2. index na radku, pretoze uz dva getc() byli
    // character = getc(file);
    // printf("character: %c\n",character);
    if (character != '\n') // uplne nahodou ak je prazdne univerzum U tak aby nevyhodil counter = 1 a pritom tam nejsou prvky..(ani nevim zda muze byt prazdny)
        (*counter)++;


    //loop for the univerzum TODO hodit na while a EOF nebude!!!!
    for(int i = 0; character != '\n' && character != EOF; i++){
        if (element_len > 30){
            fprintf(stderr, "prvek longer than 30 chars...");
            return -1;
        }

    character = getc(file);

    if (character != ' '){
        u[idx].element[element_len] = character;
    }

    // printf("idx: %d character: %c element_len: %d\n",idx, character, element_len);

    element_len++;
    (*line_length)++;

        if (character == ' ' || character == '\n' || character == EOF){
           // u[idx].index = idx;
        //    printf("element_len: %d\n", element_len);
        //    printf("element_len 0: %d\n",element_len);
            u[idx].element[element_len-1] = '\0';
            element_len = 0;
            (*counter)++;
            idx++;
        }

    }
    u[idx].element[element_len+1] = '\0';
    return 1;
}

int main(int argc, char **argv){

    printf("num of arguments %d, name of txt: %s\n",argc,argv[1]);
    Universum *u;
    Set *s;

    /*
    u[0] = {1, "heslo"}
    u[0].index = 1
    u[0].elements[0] = 'h'
    heslo
    */
// operator -> or ->* applied to "Universum" instead of to a pointer type
// set.items[j] == relation[i].first
    FILE *file;
    char *filename = argv[1];
    int counter = 0;
    int line_length = 0;
    file = fopen(filename, "r");

    if(file == NULL){
        fprintf(stderr,"This file name is invalid.");
        fclose(file);
        return -1;
    }
    //malloc
    u = malloc(100 * sizeof(int));
    s = malloc(100 * sizeof(int));

    if(u == NULL){
        fprintf(stderr,"Memory not allocated");
        return -1;
    }

    if (universum_check(file, &counter, &line_length,u)){
        printf("universum is valid and has:\n %d elements\nand line_len is: %d\n", counter, line_length);
    }
    else{
        printf("universum smrdi");
        fclose(file);
        return -1;
    }
    if(convert_to_index(file,s,u,counter)){
        printf("sucess\n");
    }
    else{
        printf("fail\n");
    }
    printf("\n");
    for(int i = 0; i < counter; i++){
        printf("\nelementy univerza:\n");
        printf("%s\n",u[i].element);
    }
    // printf("%s\n",u[2].element);
    printf("set: \n");
    for(int i = 0; i < 3 ;i++){
        printf("set:[%d] = %d \n", i, s->set[i]);
    }

    //free
    free(u);
    free(s);

    fclose(file);
    return 0;
}