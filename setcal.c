#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

typedef struct {
    char element[31];
} Universum;

typedef struct {
    int *set;
    int cardinality;
    int radek;
} Set;

typedef struct{
    int first;
    int second;
} Pairs;

typedef struct {
    Pairs *p;
    int radek;
} Relations;

typedef struct {
    Set *s;
    Universum *u;
    Relations *r;
} Main;




int set_to_index(FILE *file, Main *m, int uni_element, int *mainindex){

    //get element in temp
    //compare with uni
    //if found -> put indx in MAIN->set *s
    char temp[31];
    int index = 0;
    int element_index = 0;
    bool was_found = false;
    // main.s[*mainindex]->cardinality = 0;
    m->s[*mainindex].cardinality = 0;

    //Malloc pro jeden radek
    // main.s[*mainindex]->set = malloc(1000 * sizeof(int));
    // if(main.s->set == NULL){
    //     fprintf(stderr,"memory could not be allocated");
    //     return false;
    // }
    m->s[*mainindex].set = malloc( 1000 * sizeof(m->s->set));
    if (m->s[*mainindex].set == NULL){
        fprintf(stderr,"memory allocation was not possible.");
        return EXIT_FAILURE;
    }

    //TODO udelat separatni funkci
    char character;

    while(character != '\n' && character != EOF){
        //goes to a new character
        character = getc(file);
        if (character == ' ' || character == '\n' || character == EOF) {
            temp[index] = '\0';
            // printf("temp str: %s\n",temp);
            index = 0;
            (m->s[*mainindex].cardinality) += 1;
            // printf("setting cardinality to: %d\n", m->s[*mainindex].cardinality);
            for (int j = 0; j < uni_element; j++){

                if (strcmp(temp, m->u[j].element) == 0){
                    m->s[*mainindex].set[element_index] = j;
                    // printf("elementindex :%d\n",m->s[*mainindex].set[element_index]);
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
void set_print(Main *m, int *mainindex){

    //start of the line
    printf("S");
    // printf("mainindex %d\n", *mainindex);
    // printf("cardinality : %d\n", m->s[*mainindex].cardinality);
    for (int i = 0; i < 5; i++){
        printf(" ");
        printf("%s",m->u[m->s[*mainindex].set[i]].element);
    }
    printf("\n");

// [5,0,4]
}

//TODO - dat inkrementaci na konec
int universum_check(FILE *file, int *counter, int *line_length, Main *m){
    int element_len = 0;
    int idx = 0;
    char character = getc(file);

    for(int i = 0; character != '\n' && character != EOF; i++){
        if (element_len > 30){
            fprintf(stderr, "prvek longer than 30 chars...");
            return -1;
        }

    character = getc(file);
    if (character != ' '){
        m->u[idx].element[element_len] = character;
    }
    // printf("idx: %d character: %c element_len: %d\n",idx, character, element_len);
    element_len++;
    (*line_length)++;

        if (character == ' ' || character == '\n' || character == EOF){
           // u[idx].index = idx;
        //    printf("element_len: %d\n", element_len);
        //    printf("element_len 0: %d\n",element_len);
            m->u[idx].element[element_len-1] = '\0';
            element_len = 0;
            (*counter)++;
            idx++;
        }
    }
    if (character != '\n') // uplne nahodou ak je prazdne univerzum U tak aby nevyhodil counter = 1 a pritom tam nejsou prvky..(ani nevim zda muze byt prazdny)
        (*counter)++;
    m->u[idx].element[element_len+1] = '\0';
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
int is_type_correct(int first_element, int second_element){
    if (first_element != 'S' && first_element != 'R' && first_element != 'C' && second_element != ' ')
        return 0;
    return 1;
}

int typecheck(FILE *file){
    int type = getc(file);

    if (type == EOF)
        return EOF;

    int space = getc(file);

    if (!is_type_correct(type,space)){
        fprintf(stderr, "ERR: Neznama definice typu/univerzum redefinovane\n");
        printf("nasel sem char %c a char %c", type, space);
        return 0;
    }
    return type;
}

    
int main(int argc, char **argv){

    printf("num of arguments %d, name of txt: %s\n",argc,argv[1]);
    Main *m;
    FILE *file;
    char *filename = argv[1];
    int counter = 0;
    int line_length = 0;
    int mainindex = 0;
    file = fopen(filename, "r");

    if(file == NULL){
        fprintf(stderr,"This file name is invalid.");
        fclose(file);
        return -1;
    }
    // if(malloc_structs(s,u) == false){
    //     return EXIT_FAILURE;
    // }
    m = malloc(sizeof(m));
    if (m == NULL){
        fprintf(stderr,"memory allocation was not possible.");
        return EXIT_FAILURE;
    }
    m->u = malloc(1000 * sizeof(char));
    if(m->u == NULL){
        fprintf(stderr,"memory allocation was not possible.");
        return EXIT_FAILURE;
    }
    //maloc pro set
    m->s = malloc(1000 * sizeof(int));
    if (m->s == NULL){
        fprintf(stderr,"memory allocation was not possible.");
        return EXIT_FAILURE;
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

    INIT
    ----
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
    if(universum_check(file, &counter, &line_length,m)){
        printf("universum is valid and has:\n %d elements\nand line_len is: %d\n", counter, line_length);
    }
    else{
        printf("universum smrdi");
        fclose(file);
        return -1;
    }

    int ret = typecheck(file);
    printf("ret before while: %c\n", ret);
    while(ret != EOF){
        printf("ret: %c\n", ret);
        if (ret == 0){
            return 0;
        }
        if(ret == 'S'){
            if(set_to_index(file,m,counter, &mainindex)){
                printf("sucess printing set num:%d\n",mainindex);
                printf(" ");
                set_print(m, &mainindex);
                mainindex++;
            }
            else{
                printf("fail\n");
                //free funkce
                return EXIT_FAILURE;
            }
        }
        // if(typecheck == 'R'){
        //     break;
        // }

        // if (typecheck == 'C'){
        //     break;
        // }
        ret = typecheck(file);
    }

    // printf("setting cardinality to: %d\n", m->s[1].cardinality);

    // printf("\n");
    // printf("\nelementy univerza: \n");

    // // printf("%s\n",u[2].element);
    // printf("set 1: \n");
    // for(int i = 0; i < m->s[0].cardinality;i++){ //s->cardinality
    //     printf("set:[%d] = %d \n", i, m->s[0].set[i]); //s->set[i]);
    // }
    // printf("cardinality: %d\n", m->s[1].cardinality);

    // printf("set 2 : \n");
    // for(int i = 0; i < 5;i++){ //s->cardinality
    //     printf("set:[%d] = %d \n", i, m->s[1].set[i]); //s->set[i]);
    // }
    // printf("set1 = %d \n", m->s[1].set[4]);

    //free memory
    free(m->s->set);
    free(m->u);
    free(m->s);
    free(m);

    fclose(file);
    return 0;
}