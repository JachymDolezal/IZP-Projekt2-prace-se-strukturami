/*
Authors:
@FrodoCZE login: xdolez0c
@Midiros login: xlegne
@youruncle1 login: xpolia05

Last updated 27.11.2021 2 p.m.
*/

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

typedef struct {
    char element[31];
} Universum_elements;

typedef struct {
    int universum_cardinality;
    int capacity;
    Universum_elements *element;
} Universum;

typedef struct{
    int *set_items;
    int capacity;
    int cardinality;
    int line_index;
} Set_line;

typedef struct{
    Set_line *l;
    int line_capacity;
} Sets;

typedef struct{
    int first;
    int second;
} Pairs;

typedef struct {
    Pairs *p;
    int cardinality;
    int capacity;
    int line_index;
} Relation_line;

typedef struct {
    Relation_line *l;
    int line_capacity;
} Relations;

typedef struct{
    Sets s; // m.s->l[idx]->set
    Universum u;
    Relations r;

} Main;

int *allocate_or_resize(int *arr, unsigned int size){
    
    int *new_arr = (int*)realloc(arr, size);
    if (new_arr == NULL){
        free(arr);
        return NULL;
    }

    return new_arr;
}

Set_line *set_ctor(int line){

    Set_line *set = malloc(sizeof(Set_line));
    if (set == NULL)
        return NULL;
    set->set_items = NULL;
    set->capacity = 0;
    set->cardinality = 0;
    set->line_index = line;
    return set;
}

//prints a set
void set_print(int cardinality, int *array){
    printf("S ");
    for (int i = 0; i < cardinality; i++){
        printf("%d ",array[i]);
    }
    printf("\n");
}

// void relation_print(Main *m){
//     printf("relace!");
// }

int set_to_index(FILE *file, Main *m){

    //get element in temp
    //compare with uni
    //if found -> put indx in MAIN->set *s
    int set_line_index = m->set_line;
    char temp[31];
    int index = 0;
    int element_index = 0;
    bool was_found = false;
    // main.s[*mainindex]->cardinality = 0;
    m->s[set_line_index].cardinality = 0;

    //Malloc pro jeden radek
    m->s[set_line_index].set = malloc( 1000 * sizeof(m->s->set));
    if (m->s[set_line_index].set == NULL){
        fprintf(stderr,"memory allocation was not possible.");
        return EXIT_FAILURE;
    }

    //TODO udelat separatni funkci
    char character = 'd';

    while(character != '\n' && character != EOF){
        //goes to a new character
        character = getc(file);
        if (character == ' ' || character == '\n' || character == EOF) {
            temp[index] = '\0';
            // printf("temp str: %s\n",temp);
            index = 0;
            (m->s[set_line_index].cardinality) += 1;
            // printf("setting cardinality to: %d\n", m->s[*mainindex].cardinality);
            //
            for (int j = 0; j < m->universum_cardinality; j++){

                if (strcmp(temp, m->u[j].element) == 0){
                    m->s[set_line_index].set[element_index] = j;
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

int relation_to_index(FILE *file, Main *m){

    bool first_word_loaded = false;
    bool second_word_loaded = false;

    char temp[31];
    int index = 0;

    char character = 'd';
    int element_index = 0;
    int line_index = m->rel_line;
    bool was_found = false;

    int relation_line_index = m->r->radek;
    //vars

    m->r[relation_line_index].p = malloc(1000 * sizeof(m->r->p));
    if(m->r[relation_line_index].p == NULL){
        fprintf(stderr, "memory allocation was not possible");
        return EXIT_FAILURE;
    }


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
                    for (int j = 0; j < m->universum_cardinality; j++){

                        if (strcmp(temp, m->u[j].element) == 0){
                            m->r[line_index].p[element_index].first = j;
                            was_found = true;
                            break;
                        }
                    }
                    if (!was_found){
                        fprintf(stderr, "Prvek neni z univerza\n");
                        return false;
                    }
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
                    for (int j = 0; j < m->universum_cardinality; j++){

                        if (strcmp(temp, m->u[j].element) == 0){
                            m->r[line_index].p[element_index].second = j;
                            was_found = true;
                            break;
                        }
                    }
                    if (!was_found){
                        fprintf(stderr, "Prvek neni z univerza\n");
                        return false;
                    }
                    index = 0;
                    strcpy(temp,"");
                    second_word_loaded = true;
                    continue;
                }
                // printf("second_word: %c\n", character);
            }
            if(second_word_loaded && first_word_loaded){
                first_word_loaded = false;
                second_word_loaded = false;
                element_index++;
            }
        }
    }

    return 0;
}


/*

R (hello bye) (bye sorry) (sorry now)/n


*/

// int relation_to_index(FILE *file, Main *m){
//     return 0;
// }

//TODO - zmenit pro n setu
//old set_print
// void set_print(Main *m, int *mainindex){

//     //start of the line
//     printf("S");
//     // printf("mainindex %d\n", *mainindex);
//     // printf("cardinality : %d\n", m->s[*mainindex].cardinality);
//     for (int i = 0; i < 5; i++){
//         printf(" ");
//         printf("%s",m->u[m->s[*mainindex].set[i]].element);
//     }
//     printf("\n");

// [5,0,4]
// }

//TODO - dat inkrementaci na konec
int universum_check(FILE *file, Main *m){

    //tento character a space je totalni kktina, ale ak das getc(file) do if statementu, tak to proste netriggerne tu funkciu..
    char character = getc(file);
    char space = getc(file);
    if (character != 'U' && space != ' '){
        fprintf(stderr, "ERROR: Invalid universe definition!");
        return -1;
    }

    character = getc(file); //mozno do zaciatku while loopu..
    int element_len = 0;
    int idx = 0;
    m->universum_cardinality = 1;

    while (character != '\n' && character != EOF){
        if (element_len > 29){
            fprintf(stderr,"ERROR: Element in UNIVERSE exceeds 30 characters!");
            return -1;
        }
        if (character != ' '){
            m->u[idx].element[element_len] = character;
            element_len++;
        }
        if (character == ' '){
            m->u[idx].element[element_len+1] = '\0';
            element_len = 0;
            idx++;
            m->universum_cardinality += 1;
        }
        character = getc(file);
    }
    printf("po while je character: %c\n", character);
    return 1;
    
    // int element_len = 0;
    // int idx = 0;
    // char character = getc(file);
    // printf("%c\n", character);
    // getc(file);

    // for(int i = 0; character != '\n' && character != EOF; i++){
    //     if (element_len-1 > 30){
    //         fprintf(stderr, "prvek longer than 30 chars...");
    //         return -1;
    //     }

    //     character = getc(file);
    //     printf("char: %c\n", character);
    //     if (character != ' '){
    //         m->u[idx].element[element_len] = character;
    //         element_len++;
    //     }
    //     // printf("idx: %d character: %c element_len: %d\n",idx, character, element_len);
    //     (*line_length)++;

    //         if (character == ' ' || character == '\n' || character == EOF){
    //             printf("i%d:mezera\n",i);
    //         // u[idx].index = idx;
    //         // printf("element_len: %d\n", element_len);
    //         //    printf("element_len 0: %d\n",element_len);
    //             m->u[idx].element[element_len+1] = '\0';
    //             element_len = 0;
    //             (m->universum_cardinality)++;
    //             idx++;
    //         }
    // }
    // //if (character != '\n') // uplne nahodou ak je prazdne univerzum U tak aby nevyhodil universum cardinality a pritom tam nejsou prvky..(ani nevim zda muze byt prazdny)
    // //(m->universum_cardinality)++;
    // //m->u[idx].element[element_len+1] = '\0';
    // return 1;
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


//TODO
// int malloc_init(){
//     return 0;
// }

// int resize_mem(){
//     return 0;
// }

// void memory_free(int *ptr){
//     free(ptr);
// }

// int is_type_correct(int first_element, int second_element){
//     if (first_element != 'S' && first_element != 'R' && first_element != 'C' && second_element != ' ')
//         return 0;
//     return 1;
// }

// int typecheck(FILE *file){
//     int type = getc(file);

//     if (type == EOF)
//         return EOF;

//     int space = getc(file);

//     if (!is_type_correct(type,space)){
//         fprintf(stderr, "ERR: Neznama definice typu/univerzum redefinovane\n");
//         printf("nasel sem char %c a char %c", type, space);
//         return 0;
//     }
//     return type;
// }

//2 Prints out the element count/cardinality in a set.
void print_cardinality(Main *m, int set_index){
    printf("Set has : %d elements\n", m->s[set_index].cardinality);
}

//3
void do_complement(Main *m, int set_index){
    bool found;
    printf("S ");
    for (int i = 0; i < m->universum_cardinality; i++){
        found = false;
        for (int j = 0; j < m->s[set_index].cardinality; j++){
            if (m->s[set_index].set[j] == i)
                found = true;
        }
        if (!found)
            printf("%s ", m->u[i].element);
    }
}

//4.. Outputs a union of two sets.
void do_union(Main *m, int set_index_a, int set_index_b){
    bool in_union;
    int cardinality_a = m->s[set_index_a].cardinality;
    int cardinality_b = m->s[set_index_b].cardinality;
    printf("cardinlity_a: %d\n", cardinality_a);
    printf("cardinality_b: %d\n",cardinality_b);
    int *union_set = malloc((cardinality_a)+(cardinality_b)*sizeof(int)); //creates a temp array of a maximum union of the two arrays.
    int i;
    int union_cardinality = 0;

    for(i = 0; i < cardinality_a; i++){
        union_set[i] = m->s[set_index_a].set[i];
        union_cardinality++;
    }
    for(int j = 0; j < cardinality_b; j++){
        in_union = false;
        for(int k = 0; k < union_cardinality; k++){
            if(m->s[set_index_b].set[j] == union_set[k]){
                in_union = true;
            }
        }
        if(!in_union){
            union_set[i] = m->s[set_index_b].set[j];
            union_cardinality++;
            i++;
        }
    }
    printf("union_cardinality%d\n",union_cardinality);
    set_print(union_cardinality,union_set); //outputs the result
    free(union_set);

}
// 5.. Prints out intersection of two sets.

// retype to INT for malloc errors...!!!
void intersect(Main *m,int set_index_a,int set_index_b){
    int i, j;
    int cardinality_a = m->s[set_index_a].cardinality;
    int cardinality_b = m->s[set_index_b].cardinality;
    int printed_elements = 0;
    int intersect_cardinality = 0;
    int *intersect = malloc(cardinality_a*sizeof(int));
    for (i = 0; i < cardinality_a; ++i)
    {
        // printf("%d", i);
        int a_index = m->s[set_index_a].set[i];
        // printf("Tohle je a_index = %d\n", a_index);

        // printf("%c", a_index);
        for (j = 0; j < cardinality_b; j++)
        {

            int b_index = m->s[set_index_b].set[j];
            // printf("Tohle je b_index = %d\n", b_index);
            if (a_index == b_index)
            {
                intersect[intersect_cardinality] = a_index;
                // printf("%c", set_2[j]);
                intersect_cardinality++;
                continue;
            }
        }
    }
    for (printed_elements = 0; printed_elements < intersect_cardinality; printed_elements++)
    {
        printf("%d\n", intersect[printed_elements]);
    }
    free(intersect);
}

//prints true if set is empty, otherwise prints false.
bool is_empty( Main *m,int set_index){
    return m->s[set_index].cardinality > 0 ? false : true;
}

//6. prints A-B
void minus(Main *m, int set_index_a, int set_index_b){
    int cardinality_a = m->s[set_index_a].cardinality;
    int cardinality_b = m->s[set_index_b].cardinality;
    //todo, ak sa element z A nenachadza v B, mozem ho printit... that is all folks
    // dost sa mi algoritmus podoba na subseteq forsomreason to asi je to iste haha, ak !found tak printim a done
    bool element_found;
    int *difference_set = malloc(cardinality_a*sizeof(int));
    int diff_idx = 0;

    for (int i = 0; i < cardinality_a; i++){
        element_found = false;
        for (int j = 0; j < cardinality_b; j++){
            if(m->s[set_index_a].set[i] == m->s[set_index_b].set[j]){
                element_found = true;
                break;
            }
        }
        if (!element_found){
            difference_set[diff_idx] = m->s[set_index_a].set[i];
            diff_idx++;
        }
    }
    set_print(diff_idx, difference_set);
    free(difference_set);
}

//7. returns true if set A is subset of set B, otherwise returns false.
//REWORK algorithm
bool subseteq(Main *m, int set_index_a, int set_index_b){
    // [3,4]
    // [1,2,3,4,5,6,7]
    int cardinality_a = m->s[set_index_a].cardinality;
    int cardinality_b = m->s[set_index_b].cardinality;

    bool element_found;
    for(int i = 0; i < cardinality_a; i++){
        element_found = false;
        for(int j = 0; j < cardinality_b; j++){
            if(m->s[set_index_a].set[i] == m->s[set_index_b].set[j]){
                //element in set was found in set B
                element_found = true;
                break;
            }
            // else{
            //     //element was not found in set B. Hence, set A is not a subset of set B.
            //     return false;
        }
        if (!element_found){
            return false;
        }
    }
    return true;
}

// 8.
bool subset(Main *m, int set_index_a, int set_index_b){

    int cardinality_a = m->s[set_index_a].cardinality;
    int cardinality_b = m->s[set_index_b].cardinality;

    if (subseteq(m, set_index_a, set_index_b) && (cardinality_a < cardinality_b))
        return true;
    return false;
}

//9. returns true if set A is equal to set B
int compare(const void * a, const void * b) {
   return ( *(int*)a - *(int*)b );
}

//equals is...
bool equals(Main *m, int set_index_a, int set_index_b){
//https://www.cplusplus.com/reference/cstring/memcmp/
//https://www.cplusplus.com/reference/cstdlib/qsort/
    int cardinality_a = m->s[set_index_a].cardinality;
    int cardinality_b = m->s[set_index_b].cardinality;
    
    if (cardinality_a != cardinality_b)
        return false;

    qsort(m->s[set_index_a].set, cardinality_a, sizeof(int), compare); //tato funkce zmeni hodnoty v Set *s!!! snad to neni problem...
    qsort(m->s[set_index_b].set, cardinality_b, sizeof(int), compare);
    
    if (memcmp(m->s[set_index_a].set, m->s[set_index_b].set, cardinality_a*sizeof(int)) == 0)
        return true;
    return false;
}




//*************************************************************//
//************************ R E L A C E ************************//
//*************************************************************//  

bool symmetric(Main *m, int rel_index){
    // rel_index bude index kde se nachazi spravny .radek
    // m->r[rel_index].p[index_dvojice].first; 
    // m->r[rel_index].p[index_dvojice].second;

    int rel_cardinality = m->r[rel_index].cardinality;
    int a1, b1, a2, b2;
    bool found_symmetric;
  
    for (int i = 0; i < rel_cardinality; i++){
        a1 = m->r[rel_index].p[i].first;
        b1 = m->r[rel_index].p[i].second;
        found_symmetric = false;

        for (int j = 0; j < rel_cardinality; j++){

            if (j == i){
                continue;
            }

            a2 = m->r[rel_index].p[j].first;
            b2 = m->r[rel_index].p[j].second;

            if (a2 == b1 && b2 == a1){
                    found_symmetric = true;
            }
        }
        if (!found_symmetric)
            return false;
    }
    return true;
}

    //zoberem v prvej dvojici prvky, hladam dalsiu dvojicu kde sa 2.(b1) nachadza na 1.(b2), tam pozrem 2.(c1) prvok, 
    //potom cyklom hladam kde je zas 1.(a2) prvok na zaciatku, a ked je tam druhy prvok(c2) rovny (c1), nasiel sa tranzitiv na a b c.
    // takto prejdem vsetky dvojice...
bool transitive(Main *m, int rel_index){

    int rel_cardinality = m->r[rel_index].cardinality;
    int a1,b1,a2,b2,c1,c2;
    bool found_transitive;

    for (int i = 0; i < rel_cardinality; i++){
        a1 = m->r[rel_index].p[i].first;
        b1 = m->r[rel_index].p[i].second;
        found_transitive = false;

        for (int j = 0; j < rel_cardinality; j++){
            if (j == i){
                continue;
            }
            b2 = m->r[rel_index].p[j].first;
            if (b2 == b1){
                c1 = m->r[rel_index].p[j].second;

                for (int k = 0; k < rel_cardinality; k++){
                    if (k == i || k == j){
                        continue;
                    }
                    a2 = m->r[rel_index].p[k].first;
                    c2 = m->r[rel_index].p[k].second;
                    if (a2 == a1 && c2 == c1){
                        found_transitive = true;
                    }
                }
            }
        }
        if (!found_transitive){
            return false;
        }
    }
    return true;
} 

int in_array(int *arr, int arr_size, int number){
    for (int i = 0; i < arr_size; i++){
        if (*(arr+i) == number){
            return 1;
        }
    }
    return 0;
}

void domain(Main *m, int rel_index){
    int rel_cardinality = m->r[rel_index].cardinality;
    int *domain = malloc(rel_cardinality*sizeof(int));
    int x, domain_size = 0;

    for (int i = 0; i < rel_cardinality; i++){
        x = m->r[rel_index].p[i].first;
        if (!in_array(domain, domain_size, x)){
            domain[domain_size] = x;
            domain_size++;
        }
    }
    set_print(domain_size, domain);
}

int main(int argc, char **argv){

    printf("num of arguments %d, name of txt: %s\n",argc,argv[1]);
    Main *m;
    FILE *file;
    char *filename = argv[1];
    int radek = 1;
    file = fopen(filename, "r");

    if(file == NULL){
        fprintf(stderr,"This file name is invalid.");
        fclose(file);
        return -1;
    }

    //Malloc
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
    m->r = malloc(1000 * sizeof(m->r));
    if (m->r == NULL){
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
    if(universum_check(file, m)){
        printf("universum is valid and has: %d elements\n", m->universum_cardinality);
    }
    else{
        fprintf(stderr,"Error universum could not be parsed.");
        // fclose(file);
        // free(m->s->set);
        // free(m->u);
        // free(m->s);
        // free(m);
        return -1;
    }

    // int ret = typecheck(file);
    m->set_line = 0;
    int i = 0;
    char character = getc(file);
    printf("%c idx: %d\n", character,i);
    i++;
    while(character != EOF){
        if (character == 0){
            return 0;
        }
        character = getc(file);
        if(character == ' '){
            continue;
        }
        printf("%c idx: %d\n", character,i);
        i++;
        if(character == '\r')
            printf("r\n");
        if(character == '\n'){
            printf("newline\n");
        }
        if(character == EOF){
            break;
            printf("EOF\n");
        }
        if(character == 'S'){
            fgetc(file);
            if(set_to_index(file,m)){
                //printf("setline : %d\n", m->set_line);
                set_print(m->s[m->set_line].cardinality,m->s[m->set_line].set);
                m->s[m->set_line].radek = radek++;
                (m->set_line)++;
                printf("setline: %d\n", m->set_line);
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
        // ret = typecheck(file);
    }

    // do_union(m,3,4);
    // for (int i = 0; i < m->set_line; i++){
    //     printf("set %d cardinality: %d\n", i, m->s[i].cardinality);
    // }
    //free memory
    free(m->s[0].set);
    free(m->s[1].set);
    free(m->u); //problem
    // printf("test\n");
    free(m->r);
    // printf("test\n");
    free(m->s);
    free(m);
    fclose(file);

    return 0;
}