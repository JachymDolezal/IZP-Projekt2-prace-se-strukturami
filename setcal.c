#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#define ELEMENT_SIZE 30

//Structure for the universum and set.
typedef struct {
    char *element;
} Universum;

typedef struct {
    int size;
    int *set;
} Set;

typedef struct {
    int first_element;
    int second_element;
} Relations;

typedef struct{
    Universum *u;
    Set *s;
    Relations *s;
} Main;

bool argument_check(){
//todo
return 0;
}

//
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


    //loop for the univerzum
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

        if (character == ' '){
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
/*
U 123 hello abcd\n

index = 0;
element[0] = 1
element[1] = 2
element[2] = 3
element[3] = '\0'
index = 1;
element[0] =

pointer* = malloc( 31 * sizeof(str) + sizeof(int))
for()
pointer* = realloc(hello numofchars* sizeof(str) + sizeof(int))




txt
-----------
U hello hi wassup\n
adsfadsf\n
adfadsfa\n
----------
*/

// void convert_to_index(char * str,int num_of_elements, Univerzum *univerzum[]){
//     int index = 0;
//     int i = 2;
//     // Univerzum ptr->univerzum[num_of_elements];
//     while(str[i] != '\n'){

//     // univerzum[index].pozice = index;
//     // univerzum[index].element[i] = str[i];

//     if(str[i] == ' '){
//         index++;
//     }
//     if(index >= num_of_elements-1){
//         break;
//     }
//     i++;
//     index++;
//     }
// }


// void convert_from_index(){
//     return 0;
// }


// void file_opener(){
// //todo
// }

// void my_malloc(){
// //todo
// }

// bool file_check(){
// //todo
// }

// void line_parser(){
// //todo
// }

// // N funkci pro operaci kde je output struktura
// void func1_N(){
// //todo
// }

// // N funkci kde je vystup bool hodnota
// bool func_bool(){
// //todo
// }

// //prints output of a bool function
// void bool_print(){
// //todo
// }

// //outputs relation
// void relation_print(){
// //todo
// }

// // outputs set
// void set_print(){
// //todo
// }

typedef struct {
// nejak zakomponovat struktury do relací/mnozin
// pole indexu univerza??
int test;
} Struktura;


 /* reference pro prace se struktury s pointery */
    // void func(Set *u){
    //     u->size = NULL;
    //     return 0;
    // }

    // func(&universum);

int main(int argc, char **argv){

    printf("num of arguments %d, name of txt: %s\n",argc,argv[1]);

//     Set universum[] = {{0,"h"},{1,"b"},{2,"c"},{3,"d"}};

//     // S h c d b 
//     // [0,2,1,3]

    
//     mnozina set[] = { {4,{1,2,3,4}}, // 0.prvek -> s>1. radek
//                     {5,{1,2,3,5,6}},
//                     {3,{1,2,3}},
//                     {4,{1,2,3,4}},
//                     };
    
//     free(set[0])
// //     typedef struct{


//      int size;
//      int *items;

//      } vector_t;

    // v->items = malloc(size * sizeof(int));

    Universum u[3];
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

     if (universum_check(file, &counter, &line_length,u)){
        printf("universum is valid and has:\n %d elements\nand line_len is: %d", counter, line_length);
    }
    else{
        printf("universum smrdi");
        fclose(file);
        return -1;
    }
    if (universum_check(file, &counter, &line_length,u)){
        printf("universum is valid and has:\n %d elements\nand line_len is: %d", counter, line_length);
    }
    else{
        printf("universum smrdi");
        fclose(file);
        return -1;
    }
    // convert_to_index(temp_univerzum,&univerzum,counter);

    /*
    if(load_universum(file,30,&counter)){
        printf("universum is valid and has: %d elements\n",counter);
        printf("len of universum is: %d\n", line_len());
    }
    else{
        printf("universum is not valid\n");
        return -1;
    }
    Univerzum uni[counter];

    */
    


    /*
    1. funcke ktera zisti pocet prvku unvierza + checkne dlzku prvku
    2. ak 1. ret    urne 1(true) mozem ukladat prvky do arrayu struktury Univerzum
         2.1 array bude mat tvar Univerzum array[counter] = { {0, "prvniprvek"},{1,"druhyprvek"},{...},... }
         
    u hesllo hesllo hello 
    */


    /*
    ----Steps programu-----

    1. kontrola argumentu
    2. nacteni gitsouboru
    3. malloc pro obsah souboru
    4. kontrola souboru
    5. ulozeni typu:
        - univerzum
        - mnoziny/relace
        - funkce
    6. provedení funkcí na množinách/relacích
    7. prislusny tisk vysledku funkce
    8. ukončení programu

    */

    fclose(file);
    return 0;
}