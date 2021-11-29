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

#define TRUE 1
#define FALSE 0

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
} Relations;

typedef struct{
    Universum *u;
    Sets *s;
    Relations *r;

} Main;

void *allocate_or_resize(void *ptr, unsigned int size){

    void *new_arr = realloc(ptr, size);
    if (new_arr == NULL){
        free(ptr);
        return NULL;
    }

    return new_arr;
}

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


int init_universum(Main *m){
    m->u->capacity = 1;
    m->u->universum_cardinality = 0;
    m->u->elements = malloc(sizeof(Universum_elements));
    if(m->u->elements == NULL){
        return 0;
    }

    return 1;
}


int init_set(Main *m){
    m->s->line_capacity = 1;
    m->s->line_cardinality = 0;
    m->s->l = malloc(sizeof(Set_line));
    if (m->s->l == NULL){
        return 0;
    }

    return 1;
}


int init_relation(Main *m){
    m->r->l = malloc(sizeof(Relation_line));
    if (m->r->l == NULL)
        return 0;
    m->r->line_capacity = 1;

    return 1;
}

void main_dtor(Main *m, int depth){

    if(depth == 3){
        //depth 3
        for(int i = m->s->line_capacity; i >= 0; i--){
            free(m->s->l[i].set_items);
        }
        for(int j = m->r->line_capacity; j >= 0; j--){
            free(m->r->l[j].p);
        }
    }
    if(depth >= 2){
        for (int i = m->s->line_capacity; i >= 0; i--){
            free(m->s[i].l);
        }
        for (int i = m->r->line_capacity; i >= 0; i--){
            free(m->r[i].l);
        }
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
        return m;
    }
    else{
        main_dtor(m, 2);
    }

    m->s->l->set_items = allocate_or_resize(m->s->l->set_items,sizeof(Set_line));
    m->r->l->p = allocate_or_resize(m->r->l->p,sizeof(Pairs));
    if(m->s->l->set_items == NULL || m->r->l->p  == NULL){
        main_dtor(m, 3);
    }

    return NULL;
}


//prints a set
void set_print(int cardinality, int *array){
    printf("S ");
    for (int i = 0; i < cardinality; i++){
        printf("%d ",array[i]);
    }
    printf("\n");
}

// int d_tor(){

// }

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
            printf("R line!\n");
            getc(file);
        }
    }
    if (character == 'C'){
        if(getc(file) == ' ' ){
            printf("C line!\n");
            getc(file);
        }
    }
    if (character == EOF){
        return 0;
    }

    return 1;
}


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

int is_in_universum(Main *m, char *str){
    for (int j = 0; j < (m->u->universum_cardinality); j++){

        if (!(strcmp(str, m->u->elements[j].element))){
            return j;
        }
    }
    //not found
    return -1;
}

int set_add_element(Main *m, int element_index, int idx){

    int line_cardinality = m->s->line_cardinality;

    if (m->s->l->cardinality + 1 > m->s->l->capacity){

        m->s->l->capacity = m->s->l->capacity*2 + 1;
        m->s->l->set_items = allocate_or_resize(m->s->l->set_items, m->s->l->capacity*sizeof(int));
        if((m->u->elements) == NULL){
            return false;
        }
    }
    m->s->l[line_cardinality].set_items[idx] = element_index;
    (m->s->l->cardinality)++;
    return -1;
}

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

int main(int argc, char *argv[])
{
    FILE *file;

    printf("argc:%d argv[%d]: %s\n",argc,1,argv[1]);

    char *filename = argv[1];

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

    //if typecheck(file) == 'U'
    //uniload;
    //else fail;

    //uni_set_created

    // setsl[] []
    //while
    while(1){
       int return_value = type_check(file);
       if (return_value == 2){
           load_universum(file, m);
       }
       if (return_value == 3){
           set_to_index(file,m);
       }
        if(!return_value){
            break;
        }
    }
    printf("\n****UNIVERSUM:****\ncardinality: %d\n capacity: %d\n",m->u->universum_cardinality, m->u->capacity);
    for(int i = 0; i < m->u->universum_cardinality; i++){
        printf("u%d: %s\n", i, m->u->elements[i].element);
    }
    for(int i = 0; i < m->s->l->cardinality; i++){
        printf("S %d: %d\n", i, m->s->l->set_items[i]);
    }
    //dtor
    main_dtor(m,2);
    fclose(file);
    return 0;
}
