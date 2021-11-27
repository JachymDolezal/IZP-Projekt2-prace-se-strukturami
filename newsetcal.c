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
    Universum_elements *e;
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
    m->u->e = malloc(sizeof(Universum_elements));
    if(m->u->e == NULL){
        return 0;
    }

    return 1;
}


int init_set(Main *m){
    m->s->line_capacity = 1;
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
        free(m->u->e);
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
            printf("U line!\n");
            getc(file);
        }
    }
    if (character == 'S'){
        if(getc(file) == ' '){
            printf("S line!\n");
            getc(file);
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
        if(!return_value){
            break;
        }
    }

    //dtor
    main_dtor(m,2);
    fclose(file);
    return 0;
}
