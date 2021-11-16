#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

typedef struct {
    //int index;
    char element[31];
} Universum;

typedef struct {
    int *set;
    int cardinality;
} Set;


int set_to_index(FILE *file, Set *s, Universum *u, int uni_element){

    //get element in temp
    //compare with uni
    //if found -> put indx in Set *s
    char temp[31];
    int index = 0;
    int element_index = 0;
    bool was_found = false;
    s->cardinality = 0;

    //Malloc pro jeden radek
    s->set = malloc(50 * sizeof(int));
    if(s->set == NULL){
        fprintf(stderr,"memory could not be allocated");
        return false;
    }

    //TODO udelat separatni funkci
    char character = 'd';
    if (getc(file) != 'S' || getc(file) != ' '){
        fprintf(stderr, "Set is not defined");
        return false;
    }

    while(character != '\n' && character != EOF){
        //goes to a new character
        character = getc(file);

        if (character == ' ' || character == '\n' || character == EOF) {
            temp[index] = '\0';
            printf("temp str: %s\n",temp);
            index = 0;
            (s->cardinality)++;
            for (int j = 0; j < uni_element; j++){

                if (strcmp(temp, u[j].element) == 0){
                    printf("j\n");
                    s->set[element_index] = j;
                    printf("elementindex :%d\n",s->set[element_index]);
                    //expression must have struct or union type but it has type "Set *
                    element_index++;
                    was_found = true;
                    break;
                }
            }
            if (!was_found){
                fprintf(stderr, "Prvek neni z univerza\n");
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

//TODO - zmenit pro n setu
void index_to_set(Set *s, Universum *u){

    //start of the line
    printf("S");

    for (int i = 0; i < s->cardinality; i++){
        printf(" ");
        printf("%s",u[s->set[i]].element);
    }
    printf("\n");

// [5,0,4]
}

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
    if (character != '\n') // uplne nahodou ak je prazdne univerzum U tak aby nevyhodil counter = 1 a pritom tam nejsou prvky..(ani nevim zda muze byt prazdny)
        (*counter)++;
    u[idx].element[element_len+1] = '\0';
    return 1;
}
// int malloc_structs(Set *s, Universum *u){
//     //malloc pro univerzum
//     u = malloc(100 * sizeof(int));
//     if (u == NULL){
//         fprintf(stderr,"memory allocation was not possible.");
//         return false;
//     }
//     //maloc pro set
//     s = malloc(100 * sizeof(int));
//     if (s == NULL){
//         fprintf(stderr,"memory allocation was not possible.");
//         return false;
//     }
//     return 0;
// }
// udelat to aby to vracelo pointer

    /*
    malloc_structs(){
    1. malloc -> u (done)
    2. malloc -> 1000 radku * const = sizeof(set struct) 100 * 12 = 12000 bytes s[n radku] (done)
    }
    **funkce**
    3. malloc -> pro kazdy set struct 100 v radku 100 * sizeof(int) = 400 bytes  * 100 || loop(n krat) => s[n]->set malloc(400 bytes)

    tot memory allocated = 10 000 bytes

    kazdy zapis bude odecten z tot memory allocated

    free(){
        free(main)

        1. m.u
        2. m.s[n].set
        3. m.r[r].r[2]

    **potom**
    malloc na relace

    */
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
    // if(malloc_structs(s,u) == false){
    //     return EXIT_FAILURE;
    // }
    u = malloc(100 * sizeof(u));
    if (u == NULL){
        fprintf(stderr,"memory allocation was not possible.");
        return false;
    }
    //maloc pro set
    s = malloc(100 * sizeof(s));
    if (s == NULL){
        fprintf(stderr,"memory allocation was not possible.");
        return false;
    }
    //maloc pro set
    // s->set = malloc(100 * sizeof(int));
    // if (s->set == NULL){
    //     fprintf(stderr,"memory allocation was not possible.");
    //     return EXIT_FAILURE;
    // }

    /*
    plan pro main
    Variables
    File
    Malloc

    - Universum parser
    - check if universum has unique elements

    while(not eof){
        decides with what letter the new line starts and checks if it is valid (S/R/C)
        -Set parser
        -Relation parser
        -function parser
            -does function
            -outputs set/true,false
    }
    free memory
    closes the file
    return 0;

    */

    if(universum_check(file, &counter, &line_length,u)){
        printf("universum is valid and has:\n %d elements\nand line_len is: %d\n", counter, line_length);
    }
    else{
        printf("universum smrdi");
        fclose(file);
        return -1;
    }
    if(set_to_index(file,s,u,counter)){
        printf("sucess\n");
    }
    else{
        printf("fail\n");
        return EXIT_FAILURE;
    }
    printf("\n");
    printf("\nelementy univerza: \n");
    for(int i = 0; i < counter; i++){
        printf("%s\n",u[i].element);
    }
    // printf("%s\n",u[2].element);
    printf("set: \n");
    for(int i = 0; i < s->cardinality ;i++){
        printf("set:[%d] = %d \n", i, s->set[i]);
    }

    index_to_set(s, u);

    //free
    free(s->set);
    free(s);
    free(u);

    fclose(file);
    return 0;
}