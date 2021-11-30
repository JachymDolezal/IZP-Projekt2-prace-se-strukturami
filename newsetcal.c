/*
Authors:
@FrodoCZE login: xdolez0c
@Midiros login: xlegne
@youruncle1 login: xpolia05

Last updated 30.11.2021 0:30 a.m.
*/

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#define TRUE 1
#define FALSE 0

/**
 * @brief 
 * 
 * @param m 
 * @param element 
 * @param idx 
 * @return int 
 */

typedef struct {
    char element[31];
} Universum_elements;

typedef struct {
    Universum_elements *elements;
    int universum_cardinality;
    int capacity;
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
    int line_cardinality;
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
    int line_cardinality;
} Relations;

typedef struct{
    Universum *u;
    Sets *s;
    Relations *r;

} Main;


/**
 * @brief 
 * 
 * @param ptr 
 * @param size 
 * @return void* 
 */
void *allocate_or_resize(void *ptr, unsigned int size){

    void *new_arr = realloc(ptr, size);
    if (new_arr == NULL){
        free(ptr);
        return NULL;
    }

    return new_arr;
}

/**
 * @brief Set the ctor object
 * 
 * @param line 
 * @return Set_line* 
 */
Set_line *set_ctor(int line){

    Set_line *set = malloc(sizeof(Set_line));
    if (set == NULL)
        return NULL;
    set->set_items = NULL;
    set->capacity = 1;
    set->cardinality = 0;
    set->line_index = line;
    return set;
}

/**
 * @brief 
 * 
 * @param line 
 * @return Relation_line* 
 */
Relation_line *relation_ctor(int line){

    Relation_line *rel = malloc(sizeof(Relation_line));
    if (rel == NULL){
        return NULL;
    }
    rel->p = NULL;
    rel->capacity = 1;
    rel->cardinality = 0;
    rel->line_index = line;

    return rel;
}

/**
 * @brief 
 * 
 * @param m 
 * @return int 
 */
int init_universum(Main *m){
    m->u->capacity = 1;
    m->u->universum_cardinality = 0;
    m->u->elements = malloc(sizeof(Universum_elements));
    if(m->u->elements == NULL){
        return 0;
    }

    return 1;
}

/**
 * @brief 
 * 
 * @param m 
 * @return int 
 */
int init_set(Main *m){
    m->s->line_capacity = 1;
    m->s->line_cardinality = 0;
    m->s->l = malloc(sizeof(Set_line));
    if (m->s->l == NULL){
        return 0;
    }

    return 1;
}

/**
 * @brief 
 * 
 * @param m 
 * @return int 
 */
int init_relation(Main *m){
    m->r->l = malloc(sizeof(Relation_line));
    if (m->r->l == NULL)
        return 0;
    m->r->line_cardinality = 0;
    m->r->line_capacity = 1;

    return 1;
}

/**
 * @brief 
 * 
 * @param m 
 * @param depth 
 */
void main_dtor(Main *m, int depth){
    if(depth == 3){
        //depth 3
        for(int i = m->s->line_cardinality-1; i >= 0; i--){
            free(m->s->l[i].set_items);
        }
        for(int j = m->r->line_cardinality-1; j >= 0; j--){
            free(m->r->l[j].p);
        }
    }
    if(depth >= 2){
        free(m->r->l);
        free(m->s->l);
        free(m->u->elements);
    }
    if(depth >= 1){
        free(m->u);
        free(m->s);
        free(m->r);
    }
    if (depth >= 0){
        free(m);
    }
}

/**
 * @brief 
 * 
 * @return Main* 
 */
Main *main_ctor(){

    Main *m = malloc(sizeof(Main));
    if (m == NULL)
        return NULL;
    m->u = malloc(sizeof(Universum));
    m->s = malloc(sizeof(Sets));
    m->r = malloc(sizeof(Relations));
    if (m->u == NULL || m->s == NULL || m->r == NULL){
        main_dtor(m, 1);
        return NULL;
    }
    if (init_universum(m) && init_set(m) && init_relation(m)){
        m->s->l->set_items = allocate_or_resize(m->s->l->set_items,sizeof(Set_line));
        m->r->l->p = allocate_or_resize(m->r->l->p,sizeof(Pairs));
        if(m->s->l->set_items == NULL || m->r->l->p  == NULL){
            main_dtor(m, 3);
            return NULL;
        }   
        return m;
    }
    else{
        main_dtor(m, 2);
    }
    return NULL;
}

/**
 * @brief 
 * 
 * @param file 
 * @return int 
 */
int type_check(FILE *file){
    char character = getc(file);

    if (character == 'U'){
        if(getc(file) == ' '){
            return 2;
        }
    }
    if (character == 'S'){
        if(getc(file) == ' '){
            return 3;
        }
    }
    if (character == 'R'){
        if(getc(file) == ' ' ){
            return 4;
        }
    }
    if (character == 'C'){
        if(getc(file) == ' ' ){
            return 5;
        }
    }
    if (character == EOF){
        return 0;
    }

    return 1;
}

/**
 * @brief 
 * 
 * @param m 
 * @param element 
 * @param idx 
 * @return int 
 */
int uni_add_element(Main *m, char *element, int idx){
    if (m->u->universum_cardinality + 1 > m->u->capacity){

        m->u->capacity = m->u->capacity*2 + 1;
        m->u->elements = allocate_or_resize(m->u->elements, m->u->capacity*sizeof(Universum_elements));
        if ((m->u->elements) == NULL)
            return false;
    }
    strcpy(m->u->elements[idx].element, element);
    (m->u->universum_cardinality)++;
    return TRUE;
}

/**
 * @brief 
 * 
 * @param m 
 * @param element 
 * @param idx 
 * @return int 
 */
int load_universum(FILE *file, Main *m){
    char element[31];
    char character;
    int idx = 0; // idx = m->u->universum_cardinality ????? mam pocit ze hej
    int element_len = 0;

    character = getc(file);


    while (character != '\n' && character != EOF){
        if (element_len > 29){
            fprintf(stderr,"ERROR: Element defined in universe longer than 30 characters!");
            return -1;
        }

        if (character != ' '){
            element[element_len++] = character;
        }
        // printf("character: %c\n", character);
        character = getc(file);
        if (character == ' ' || character == '\n'){
            element[element_len] = '\0';
            uni_add_element(m, element, idx);
            if (m->u->elements[idx].element == NULL){
                fprintf(stderr, "ERROR: Memory allocation failure...");
                return -1;
            }
            idx++;
            element_len = 0;
            strcpy(element, "");
        }
    }
    return 1;
}

/**
 * @brief
 *
 * @param m
 * @param element
 * @param idx
 * @return int
 */
int is_in_universum(Main *m, char *str){
    for (int j = 0; j < (m->u->universum_cardinality); j++){

        if (!(strcmp(str, m->u->elements[j].element))){
            return j;
        }
    }
    //not found
    return -1;
}

/**
 * @brief 
 * 
 * @param m 
 * @param element 
 * @param idx 
 * @return int 
 */
int set_add_element(Main *m, int element_index, int idx){
    int line_cardinality = m->s->line_cardinality;
    //printf("line cardinality :%d\n", line_cardinality);
    //printf("m->s->l[%d].cardinality: %d\n",line_cardinality, m->s->l[line_cardinality].cardinality);
    if (m->s->l[line_cardinality].cardinality + 1 > m->s->l[line_cardinality].capacity){
        m->s->l[line_cardinality].capacity = m->s->l[line_cardinality].capacity*2 + 1;
        m->s->l[line_cardinality].set_items = allocate_or_resize(m->s->l[line_cardinality].set_items, m->s->l[line_cardinality].capacity*sizeof(int));
        if((m->s->l[line_cardinality].set_items) == NULL){
            fprintf(stderr, "Memory for set could not be allocated\n");
            return false;
        }
    }
    //printf("m->s->l[%d].set_items ptr: %p\n", line_cardinality, m->s->l[line_cardinality].set_items);
    
    m->s->l[line_cardinality].set_items[idx] = element_index;
    (m->s->l[line_cardinality].cardinality)++;
    return -1;
}

/**
 * @brief
 *
 * @param m
 * @param element
 * @param idx
 * @return int
 */
int set_to_index(FILE *file, Main *m){


    char character = getc(file);
    char element[31];
    int element_len = 0;
    int idx = 0;
    int set_index = 0;

    while (character != '\n' && character != EOF){
        if (character != ' '){
            element[element_len++] = character;
        }
        character = getc(file);
        if (character == ' ' || character == '\n'){
            element[element_len] = '\0';
            set_index = is_in_universum(m, element);
            if (set_index != -1){
                set_add_element(m, set_index, idx);
                if(m->s->l->set_items == NULL){
                    fprintf(stderr, "ERROR: Memory allocation failure...\n");
                    return -1;
                }
                idx++;
                element_len = 0;
                strcpy(element, "");
            }
            else{
                fprintf(stderr,"element is not in universum\n");
                return -1;
            }
        }

    }
    return 1;
}

/**
 * @brief
 *
 * @param m
 * @param element
 * @param idx
 * @return int
 */
int relation_add_element(Main *m, int element_index, bool isfirst, int idx){

    int ln_car = m->r->line_cardinality;

    if (m->r->l[ln_car].cardinality + 1 > m->r->l[ln_car].capacity){
        m->r->l[ln_car].capacity = m->r->l->capacity*2 + 1;
        m->r->l[ln_car].p = allocate_or_resize(m->r->l[ln_car].p, m->r->l[ln_car].capacity*sizeof(m->r->l[ln_car].p));
        if((m->r->l[ln_car].p) == NULL){
            return false;
        }
    }
    if(isfirst){
        m->r->l[ln_car].p[idx].first = element_index;
    }
    if(!isfirst){
        m->r->l[ln_car].p[idx].second = element_index;
        (m->r->l[ln_car].cardinality)++;
    }
    return -1;
}

/**
 * @brief
 *
 * @param m
 * @param element
 * @param idx
 * @return int
 */
int relation_to_index(FILE *file, Main *m){

    bool first_word_loaded = false;
    bool second_word_loaded = false;
    char temp[31];
    int index = 0;
    char character;
    int idx = 0;
    character = 'd';

    while(character != '\n' && character != EOF){
        character = getc(file);
        if(character == '('){
            while(character != ' '){
                character = getc(file);
                if(character != ' ')
                    temp[index++] = character;
            }
            temp[index] = '\0';
            index = 0;
            // load first word
            if((is_in_universum(m,temp)) != -1){
                relation_add_element(m,is_in_universum(m,temp),1,idx);
            }
            strcpy(temp,"");
            first_word_loaded = true;
            while(character != ')'){
                character = getc(file);
                if(character != ')')
                    temp[index++] = character;
            }
            temp[index] = '\0';
            index = 0;
            // load second word
            if((is_in_universum(m,temp)) != -1){
                relation_add_element(m,is_in_universum(m,temp),0,idx);
            }
            strcpy(temp,"");
            second_word_loaded = true;
            if(second_word_loaded && first_word_loaded){
                idx++;
                first_word_loaded = false;
                second_word_loaded = false;
            }
        }
    }

    return 0;
}

/**
 * @brief
 *
 * @param m
 * @param element
 * @param idx
 * @return int
 */
int function_parser(FILE *file){
    char temp[31];
    int index = 0;
    int character = fgetc(file);
    temp[index] = character;
    int func_num = 0;

    char functions[19][14] = {
        //1 input 0-9
        {"empty"},
        {"card"},
        {"complement"},
        {"reflexive"},
        {"symmetric"},
        {"antisymmetric"},
        {"transitive"},
        {"function"},
        {"domain"},
        {"codomain"},
        //2 inputs 10-15
        {"union"},
        {"intersect"},
        {"minus"},
        {"subseteq"},
        {"subset"},
        {"equals"},
        // 3 inputs 16-18
        {"injective"},
        {"surjective"},
        {"bijective"}
        };

    while(character != ' ' && character != '\n'){
        temp[index++] = character;
        character = fgetc(file);
        if(character == ' '){
            temp[index] = '\0';
            for(func_num = 0; func_num < 18; func_num++){
                if(strcmp(temp,functions[func_num]) == 0){
                    printf("functionname: %s\n", functions[func_num]);
                }
            }
        }

    }
    // if (func_num < 9){
    //     func_num = 1;
    //     //1x getc -> input, newline/eof
    // }
    // if (func_num > 9 && func_num < 15){
    //     func_num = 2;
    //     //input mezera input newline/eof
    // }
    // else{
    //     func_num = 3;
    //     //input mezera input mezera input newline/eof
    // }
    // //keyword -> space -> num1 -> ifspace -> num 2
    // for (j < func_num){
    //     getc() input
    //     getc() medzera,newline, eof
    // }
return true;
}

/**
 * @brief
 *
 * @param m
 */
void print_universum(Main *m){
// U -> element -> mezera until last element -> \n
    printf("U ");
    for(int i = 0 ; i < m->u->universum_cardinality; i++){
        printf("%s",m->u->elements[i].element);
        printf(" ");
    }
    printf("\n");
}

/**
 * @brief
 *
 * @param m
 * @return int
 */
void print_set(Main *m){

    int uni_index = 0;
    int line_cardinality = m->s->line_cardinality;

    printf("S ");
    for(int i = 0; i < m->s->l[line_cardinality].cardinality; i++){
        uni_index = m->s->l[line_cardinality].set_items[i];
        printf("%s ", m->u->elements[uni_index].element);

    }
    printf("\n");
}

/**
 * @brief
 *
 * @param m
 * @return int
 */

void print_relation(Main *m){
    //R ->( -> element1 -> mezera -> element2 ->) -> until last pair -> \n

    int rel_index = 0;
    int line_cardinality = m->r->line_cardinality;

    printf("R ");
    for(int i = 0; i < m->r->l[line_cardinality].cardinality; i++){
        rel_index = m->r->l[line_cardinality].p[i].first;
        printf("(%s ", m->u->elements[rel_index].element);
        rel_index = m->r->l[line_cardinality].p[i].second;
        printf("%s) ", m->u->elements[rel_index].element);
    }
    printf("\n");
}

int relation_line_add(Main *m, int line_index){
    int line_cardinality = m->r->line_cardinality;

    if (m->r->line_cardinality + 1 > m->r->line_capacity){
        m->r->line_capacity = m->r->line_capacity*2 + 1;
        m->r->l = allocate_or_resize(m->r->l, m->r->line_capacity*sizeof(Relation_line));
        if(m->r->l == NULL){
            fprintf(stderr, "Memory could not be allocated\n");
            return -1;
        }
    }
    m->r->l[line_cardinality].line_index = line_index;
    //set_ctor(line_index);

    return true;
}

int set_line_add(Main *m, int line_index){
    int line_cardinality = m->s->line_cardinality;

    if (m->s->line_cardinality + 1 > m->s->line_capacity){
        m->s->line_capacity = m->s->line_capacity*2 + 1;
        m->s->l = allocate_or_resize(m->s->l, m->s->line_capacity*sizeof(Set_line));
        if(m->s->l == NULL){
            fprintf(stderr, "Memory could not be allocated\n");
            return -1;
        }
    }
    m->s->l[line_cardinality].line_index = line_index;
    //set_ctor(line_index);

    return true;
}
/**
 * @brief
 *
 * @param m
 * @param element
 * @param idx
 * @return int
 */
int main(int argc, char *argv[]){
    FILE *file;

    printf("argc:%d argv[%d]: %s\n",argc,1,argv[1]);

    char *filename = argv[1];
    int line_index = 0;
    file = fopen(filename, "r");

    if(file == NULL){
        fprintf(stderr, "This file name is invalid");
        fclose(file);
        return -1;
    }

    //init
    Main *m = main_ctor();
    if (m == NULL){
        fclose(file);
        return 1;
    }

    while(1){
        int return_value = type_check(file);
        if (return_value == 2){
            load_universum(file, m);
            print_universum(m);
        }
        if (return_value == 3){
            set_line_add(m,line_index);
            set_to_index(file,m);
            print_set(m);
            (m->s->line_cardinality)++;
        }
        if (return_value == 4){
            relation_line_add(m,line_index);
            relation_to_index(file,m);
            print_relation(m);
            (m->r->line_cardinality)++;
        }
        if (return_value == 5){
            function_parser(file);
        }
        if(!return_value){
            break;
        }
        line_index++;
    }
    // while (1) {
    // }

    main_dtor(m,3);
    fclose(file);
    return 0;
}
