#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#define ELEMENT_SIZE 30

typedef struct {
    int pozice;
    char element[ELEMENT_SIZE];
} Univerzum;

bool argument_check(){
//todo
return 0;
}

int line_check(FILE *file, int *counter, int *line_length){

    int element_len = 0;
    char character = getc(file); //toto prve getc bych tu nechal kdyz budeme zobecnovat pro S R C, aby sme mohli podle prvniho pismena vedeli co s tim radkem delat
    if (character != 'U' || getc(file) != ' '){
        fprintf(stderr, "Universum not defined");
        return -1;
    }

    //loop zacina uz na 2. index na radku, pretoze uz dva getc() byli
    character = getc(file);
    if (character != '\n') // uplne nahodou ak je prazdne univerzum U tak aby nevyhodil counter = 1 a pritom tam nejsou prvky..(ani nevim zda muze byt prazdny)
        (*counter)++;

    //toto uz podle load_universum, misto for muze byt while(character != '\n'), protoze to i uz nijak nevyuzijeme
    for(int i = 0; character != '\n'; i++){
        if (element_len > 30){
            fprintf(stderr, "prvek longer than 30 chars...");
            return -1;
        }

        element_len++;
        (*line_length)++;
        character = getc(file);
        if (character == ' '){
            element_len = 0;
            (*counter)++;
        }
    }
    return 1;
}

void convert_to_index(char * str,int num_of_elements, Univerzum *univerzum[]){
    int index = 0;
    int i = 2;
    // Univerzum ptr->univerzum[num_of_elements];
    while(str[i] != '\n'){

    // univerzum[index].pozice = index;
    // univerzum[index].element[i] = str[i];

    if(str[i] == ' '){
        index++;
    }
    if(index >= num_of_elements-1){
        break;
    }
    i++;
    index++;
    }
}


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

int main(int argc, char **argv){
    printf("num of arguments %d, name of txt: %s\n",argc,argv[1]);
    Univerzum *univerzum;
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

     if (line_check(file, &counter, &line_length)){
        printf("universum is valid and has:\n %d elements\nand line_len is: %d", counter, line_length);
    }
    else{
        printf("universum smrdi");
        fclose(file);
        return -1;
    }
    char temp_univerzum[10]; //todo
    fgets(temp_univerzum,line_length,file);

    Univerzum univerzum[12]; //todo

    convert_to_index(temp_univerzum,&univerzum,counter);

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
    2. ak 1. returne 1(true) mozem ukladat prvky do arrayu struktury Univerzum
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