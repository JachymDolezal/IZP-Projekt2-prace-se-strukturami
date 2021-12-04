/*
Authors:
@FrodoCZE login: xdolez0c
@Midiros login: xlegne00
@youruncle1 login: xpolia05

Last updated 3.12.2021.
*/

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#define TRUE 1
#define FALSE 0
#define NUM_OF_KEYWORDS 21
#define KEYWORD_MAX_LEN 14

/**
 * @brief
 *
 * @param m
 * @param element
 * @param idx
 * @return int
 */

typedef struct
{
    char element[31];
} Universum_elements;

typedef struct
{
    Universum_elements *elements;
    int universum_cardinality;
    int capacity;
} Universum;

typedef struct
{
    int *set_items;
    int capacity;
    int cardinality;
    int line_index;
} Set_line;

typedef struct
{
    Set_line *l;
    int line_capacity;
    int line_cardinality;
} Sets;

typedef struct
{
    int first;
    int second;
} Pairs;

typedef struct
{
    Pairs *p;
    int cardinality;
    int capacity;
    int line_index;
} Relation_line;

typedef struct
{
    Relation_line *l;
    int line_capacity;
    int line_cardinality;
} Relations;

typedef struct
{
    Universum *u;
    Sets *s;
    Relations *r;

} Main;

void print_set(Main *m, int cardinality, int *set);
int set_line_add(Main *m, int line_index);
int set_add_element(Main *m, int element_index, int idx);\
int is_set(Main *m);

/**
 * @brief
 *
 * @param ptr
 * @param size
 * @return void*
 */
void *allocate_or_resize(void *ptr, unsigned int size)
{

    void *new_arr = realloc(ptr, size);
    if (new_arr == NULL)
    {
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
Set_line *set_ctor(int line)
{

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
Relation_line *relation_ctor(int line)
{

    Relation_line *rel = malloc(sizeof(Relation_line));
    if (rel == NULL)
    {
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
int init_universum(Main *m)
{
    m->u->capacity = 1;
    m->u->universum_cardinality = 0;
    m->u->elements = malloc(sizeof(Universum_elements));
    if (m->u->elements == NULL)
    {
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
int init_set(Main *m)
{
    m->s->line_capacity = 1;
    m->s->line_cardinality = 0;
    m->s->l = malloc(sizeof(Set_line));
    if (m->s->l == NULL)
    {
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
int init_relation(Main *m)
{
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
void main_dtor(Main *m, int depth)
{
    if (depth == 3)
    {

        // depth 3
        for (int i = m->s->line_cardinality - 1; i >= 0; i--)
        {
            free(m->s->l[i].set_items);
        }
        for (int j = m->r->line_cardinality - 1; j >= 0; j--)
        {
            free(m->r->l[j].p);
        }
    }
    if (depth >= 2)
    {
        free(m->r->l);
        free(m->s->l);
        free(m->u->elements);
    }
    if (depth >= 1)
    {
        free(m->u);
        free(m->s);
        free(m->r);
    }
    if (depth >= 0)
    {
        free(m);
    }
}

/**
 * @brief
 *
 * @return Main*
 */
Main *main_ctor()
{

    Main *m = malloc(sizeof(Main));
    if (m == NULL)
        return NULL;
    m->u = malloc(sizeof(Universum));
    m->s = malloc(sizeof(Sets));
    m->r = malloc(sizeof(Relations));
    if (m->u == NULL || m->s == NULL || m->r == NULL)
    {
        main_dtor(m, 1);
        return NULL;
    }
    if (init_universum(m) && init_set(m) && init_relation(m))
    {
        m->s->l->set_items = allocate_or_resize(m->s->l->set_items, sizeof(Set_line));
        m->r->l->p = allocate_or_resize(m->r->l->p, sizeof(Pairs));
        if (m->s->l->set_items == NULL || m->r->l->p == NULL)
        {
            main_dtor(m, 3);
            return NULL;
        }
        return m;
    }
    else
    {
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
    // printf("typecheck char: %d\n", character);
    if (character == 'U'){
        if((character = getc(file)) == '\n' || character == EOF){
            return 7; //empty uni
        }
        if (character == ' '){
            return 2;
        }
    }
    if (character == 'S'){
        if ((character = getc(file)) == '\n' || character == EOF){
            return 8; //empty set
        }
        else if (character == ' '){
            return 3;
        }
    }
    if (character == 'R'){
        if ((character = getc(file)) == '\n' || character == EOF){
            return 9; //empty relation
        }
        else if (character == ' '){
            return 4;
        }
    }
    if (character == 'C'){
        if (getc(file) == ' '){
            return 5;
        }
    }
    if (character == EOF){
        return 0;
    }
    if (character == 10){
        return 0;
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
int uni_add_element(Main *m, char *element, int idx)
{
    if (m->u->universum_cardinality + 1 > m->u->capacity)
    {

        m->u->capacity = m->u->capacity * 2 + 1;
        m->u->elements = allocate_or_resize(m->u->elements, m->u->capacity * sizeof(Universum_elements));
        if ((m->u->elements) == NULL)
            return false;
    }
    if(idx == -1){
        m->u->universum_cardinality = 0;
        
    }
    else{
        strcpy(m->u->elements[idx].element, element);
        (m->u->universum_cardinality)++;
    }
    return TRUE;
}

int find_function_keyword(char *str,bool find_function){

    int keyword_count = 20;
    char functions[NUM_OF_KEYWORDS][KEYWORD_MAX_LEN] = {
    // 1 input 0-9
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
    // 2 inputs 10-15
    {"union"},
    {"intersect"},
    {"minus"},
    {"subseteq"},
    {"subset"},
    {"equals"},
    // 3 inputs 16-18
    {"injective"},
    {"surjective"},
    {"bijective"},
    {"true"},
    {"false"},
    };
    
    if(find_function)
        keyword_count = 18;

    for (int i = 0; i < keyword_count; i++){
        if (!(strcmp(str, functions[i])))
            return i;
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
int load_universum(FILE *file, Main *m, int line_index)
{
    char element[31];
    char character;
    int idx = 0; // idx = m->u->universum_cardinality ????? mam pocit ze hej
    int element_len = 0;

    character = getc(file);

    while (character != '\n' && character != EOF)
    {
        if (element_len > 29)
        {
            fprintf(stderr, "ERROR: Element defined in universe longer than 30 characters!");
            return -1;
        }

        if (character != ' ')
        {
            element[element_len++] = character;
        }
        // printf("character: %c\n", character);
        character = getc(file);
        if (character == ' ' || character == '\n')
        {
            element[element_len] = '\0';
            if(find_function_keyword(element, 0) != -1){
                fprintf(stderr, "ERROR: Forbidden word defined in universum!");
                return -1;
            }
            uni_add_element(m, element, idx);
            if (m->u->elements[idx].element == NULL)
            {
                fprintf(stderr, "ERROR: Memory allocation failure...");
                return -1;
            }
            idx++;
            element_len = 0;
            strcpy(element, "");
        }
    }
    set_line_add(m, line_index);
    for(int i = 0; i < m->u->universum_cardinality; i++)
        set_add_element(m, i, i);
    if(!is_set(m)){
        return -1;
    }
    (m->s->line_cardinality)++;
    return 1;
}

int is_universum_valid(Main *m){
    int universum_cardinality = m->u->universum_cardinality;
    for (int i = 0; i < universum_cardinality; i++){
        for(int j = i+1; j < universum_cardinality; j++){
            if (!strcmp(m->u->elements[i].element,m->u->elements[j].element)){
                fprintf(stderr, "ERROR: Universum has duplicate elements\n");
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
int is_in_universum(Main *m, char *str)
{
    for (int j = 0; j < (m->u->universum_cardinality); j++)
    {
        if (!(strcmp(str, m->u->elements[j].element)))
        {
            return j;
        }
    }
    // not found
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
int set_add_element(Main *m, int element_index, int idx)
{
    int line_cardinality = m->s->line_cardinality;
    // printf("set_add_element line_cardinality: %d\n", line_cardinality);
    // printf("m->s->l[line_cardinality].cardinality : %d\n", m->s->l[line_cardinality].cardinality);
    // printf("m->s->l[%d].cardinality: %d\n",line_cardinality, m->s->l[line_cardinality].cardinality);
    if (m->s->l[line_cardinality].cardinality + 1 > m->s->l[line_cardinality].capacity)
    {
        m->s->l[line_cardinality].capacity = m->s->l[line_cardinality].capacity * 2 + 1;
        m->s->l[line_cardinality].set_items = allocate_or_resize(m->s->l[line_cardinality].set_items, m->s->l[line_cardinality].capacity * sizeof(int));
        if ((m->s->l[line_cardinality].set_items) == NULL)
        {
            fprintf(stderr, "Memory for set could not be allocated\n");
            return false;
        }
    }
    // printf("m->s->l[%d].set_items ptr: %p\n", line_cardinality, m->s->l[line_cardinality].set_items);
    if (element_index == -1){
        m->s->l[line_cardinality].cardinality = 0;
    }
    else{
        m->s->l[line_cardinality].set_items[idx] = element_index;
        (m->s->l[line_cardinality].cardinality)++;
    }
    return -1;
}

int is_set(Main *m){
    int line_cardinality = m->s->line_cardinality;
    int set_cardinality = m->s->l[line_cardinality].cardinality;
    int num1, num2 = 0;
    // printf("is_set:\nline_cardinality: %d\nset_cardinality: %d\n", line_cardinality, set_cardinality);
    // [1,0,2,3,2,4]
    for (int i = 0; i < set_cardinality; i++){
        num1 = m->s->l[line_cardinality].set_items[i];
        for(int j = i+1; j < set_cardinality; j++){
            num2 = m->s->l[line_cardinality].set_items[j];
            if (num1 == num2){
                fprintf(stderr,"Element cannot be twice in Universe/Set.\n");
                return 0;
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
int set_to_index(FILE *file, Main *m)
{

    char character = getc(file);
    char element[31];
    int element_len = 0;
    int idx = 0;
    int set_index = 0;

    while (character != '\n' && character != EOF)
    {
        if (character != ' ')
        {
            element[element_len++] = character;
        }
        character = getc(file);
        if (character == ' ' || character == '\n' || character == EOF)
        {
            element[element_len] = '\0';
            set_index = is_in_universum(m, element);
            if (set_index != -1)
            {
                set_add_element(m, set_index, idx);
                if (m->s->l->set_items == NULL)
                {
                    fprintf(stderr, "ERROR: Memory allocation failure...\n");
                    return -1;
                }
                idx++;
                element_len = 0;
                strcpy(element, "");
            }
            else
            {
                fprintf(stderr, "ERROR: Set element is not in universum\n");
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
int relation_add_element(Main *m, int element_index, bool isfirst, int idx)
{

    int ln_car = m->r->line_cardinality;

    if (m->r->l[ln_car].cardinality + 1 > m->r->l[ln_car].capacity)
    {
        m->r->l[ln_car].capacity = m->r->l->capacity * 2 + 1;
        m->r->l[ln_car].p = allocate_or_resize(m->r->l[ln_car].p, m->r->l[ln_car].capacity * sizeof(m->r->l[ln_car].p));
        if ((m->r->l[ln_car].p) == NULL)
        {
            return false;
        }
    }
    if (isfirst)
    {
        m->r->l[ln_car].p[idx].first = element_index;
    }
    if (!isfirst)
    {
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
int relation_to_index(FILE *file, Main *m)
{

    bool first_word_loaded = false;
    bool second_word_loaded = false;
    char temp[31];
    int index = 0;
    char character;
    int idx = 0;
    character = 'd';

    while (character != '\n' && character != EOF){
        character = getc(file);
        if(character == ')'){
            fprintf(stderr,"Wrong relation syntax");
            return -1;
        }
        if (character == '('){
            while (character != ' '){
                character = getc(file);
                //error handling
                if(character == '(' || character == ')'){
                    fprintf(stderr,"Wrong relation syntax");
                    return -1;
                }
                if (character != ' ')
                    temp[index++] = character;
            }
            temp[index] = '\0';
            index = 0;
            // load first word
            if ((is_in_universum(m, temp)) != -1){
                relation_add_element(m, is_in_universum(m, temp), 1, idx);
            }
            else{
                return -1;
            }
            strcpy(temp, "");
            first_word_loaded = true;
            while (character != ')') {
                character = getc(file);
                if(character == ' ' || character == '('){
                    fprintf(stderr,"Wrong relation syntax");
                    return -1;
                }
                if (character != ')')
                    temp[index++] = character;
            }
            temp[index] = '\0';
            index = 0;
            // load second word
            if ((is_in_universum(m, temp)) != -1){
                relation_add_element(m, is_in_universum(m, temp), 0, idx);
            }
            else{
                return -1;
            }
            strcpy(temp, "");
            second_word_loaded = true;
            if (second_word_loaded && first_word_loaded){
                idx++;
                first_word_loaded = false;
                second_word_loaded = false;
            }
            else{
                return -1;
            }
        }
    }

    return true;
}

int set_find_index(Main *m, int line_index)
{
    for (int i = 0; i < m->s->line_cardinality; i++)
    {
        if (m->s->l[i].line_index == line_index)
            return i;
    }
    return -1;
}

int rel_find_index(Main *m, int line_index)
{
    for (int i = 0; i < m->r->line_cardinality; i++)
    {
        if (m->r->l[i].line_index == line_index)
            return i;
    }
    return -1;
}

void is_empty(Main *m, int line_index)
{
    printf("%s\n", m->s->l[line_index].cardinality > 0 ? "false" : "true");
}

// Funkce printuje prunik dvou mnozin.
void intersect(Main *m, int set_line_index_a, int set_line_index_b)
{
    int i, h;
    // int printed_elements = 0;
    int intersect_cardinality = 0;
    int *intersect = malloc(sizeof(int) * m->s->l[set_line_index_a].cardinality);
    for (i = 0; i < m->s->l[set_line_index_a].cardinality; ++i)
    {
        // printf("%d", i);
        int a_index = m->s->l[set_line_index_a].set_items[i];
        // printf("Tohle je a_index = %d\n", a_index);

        // printf("%c", a_index);
        for (h = 0; h < m->s->l[set_line_index_b].cardinality; h++)
        {

            int b_index = m->s->l[set_line_index_b].set_items[h];
            // printf("Tohle je b_index = %d\n", b_index);
            if (a_index == b_index)
            {
                intersect[intersect_cardinality] = a_index;
                // printf("%c", set_2[h]);
                intersect_cardinality++;
                continue;
            }
        }
    }
    // for (printed_elements = 0; printed_elements < intersect_cardinality; printed_elements++)
    // {
    //     printf("%d\n", intersect[printed_elements]);
    // }
    print_set(m, intersect_cardinality, intersect);
    free(intersect);
}

void do_complement(Main *m, int line_index)
{
    bool found;
    printf("S ");
    for (int i = 0; i < m->u->universum_cardinality; i++)
    {
        found = false;
        for (int j = 0; j < m->s->l[line_index].cardinality; j++)
        {
            if (m->s->l[line_index].set_items[j] == i)
                found = true;
        }
        if (!found)
            printf("%s ", m->u->elements[i].element);
    }
}

/**
 * @brief
 *
 * @param m
 * @param set_index_a
 * @param set_index_b
 */
void do_union(Main *m, int set_line_index_a, int set_line_index_b)
{
    bool in_union;
    int cardinality_a = m->s->l[set_line_index_a].cardinality;
    int cardinality_b = m->s->l[set_line_index_b].cardinality;
    int *union_set = malloc((cardinality_a) + (cardinality_b) * sizeof(int)); // creates a temp array of a maximum union of the two arrays.
    int i;
    int union_cardinality = 0;

    for (i = 0; i < cardinality_a; i++)
    {
        union_set[i] = m->s->l[set_line_index_a].set_items[i];
        union_cardinality++;
    }
    for (int j = 0; j < cardinality_b; j++)
    {
        in_union = false;
        for (int k = 0; k < union_cardinality; k++)
        {
            if (m->s->l[set_line_index_b].set_items[j] == union_set[k])
            {
                in_union = true;
            }
        }
        if (!in_union)
        {
            union_set[i] = m->s->l[set_line_index_b].set_items[j];
            union_cardinality++;
            i++;
        }
    }
    print_set(m, union_cardinality, union_set); // outputs the result
    free(union_set);
}

void minus(Main *m, int line_index_a, int line_index_b)
{
    int cardinality_a = m->s->l[line_index_a].cardinality;
    int cardinality_b = m->s->l[line_index_b].cardinality;
    bool element_found;
    int *difference_set = malloc((cardinality_a + cardinality_b) * sizeof(int));
    int diff_idx = 0;

    for (int i = 0; i < cardinality_a; i++)
    {
        element_found = false;
        for (int j = 0; j < cardinality_b; j++)
        {
            if (m->s->l[line_index_a].set_items[i] == m->s->l[line_index_b].set_items[j])
            {
                element_found = true;
                break;
            }
        }
        if (!element_found)
        {
            difference_set[diff_idx] = m->s->l[line_index_a].set_items[i];
            diff_idx++;
        }
    }
    print_set(m, diff_idx, difference_set);
    free(difference_set);
}

bool subseteq(Main *m, int line_index_a, int line_index_b)
{
    int cardinality_a = m->s->l[line_index_a].cardinality;
    int cardinality_b = m->s->l[line_index_b].cardinality;
    bool element_found;
    for (int i = 0; i < cardinality_a; i++)
    {
        element_found = false;
        for (int j = 0; j < cardinality_b; j++)
        {
            if (m->s->l[line_index_a].set_items[i] == m->s->l[line_index_b].set_items[j])
            {
                element_found = true;
                break;
            }
        }
        if (!element_found)
        {
            return false;
        }
    }
    return true;
}

int subset(Main *m, int line_index_a, int line_index_b)
{

    int cardinality_a = m->s->l[line_index_a].cardinality;
    int cardinality_b = m->s->l[line_index_b].cardinality;

    if (subseteq(m, line_index_a, line_index_b) && (cardinality_a < cardinality_b))
    {
        printf("true\n");
        return true;
    }

    printf("false\n");
    return false;
}

void equals(Main *m, int line_index_a, int line_index_b)
{
    // mame podmnoziny X,Y -> ak X je podmnozinou Y  a Y je podmnozinou X => X=Y
    if (subseteq(m, line_index_a, line_index_b) && subseteq(m, line_index_b, line_index_a))
        printf("true\n");
    else
        printf("false\n");
}

//*************************************************************//
//************************ R E L A C E ************************//
//*************************************************************//

/**
 * @brief
 *
 * @param m
 * @param line_index
 */
int symmetric(Main *m, int line_index)
{
    // rel_index bude index kde se nachazi spravny .radek
    // m->r[rel_index].p[index_dvojice].first;
    // m->r[rel_index].p[index_dvojice].second;
    int rel_cardinality = m->r->l[line_index].cardinality;
    int a1, b1, a2, b2;
    bool found_symmetric;

    for (int i = 0; i < rel_cardinality; i++)
    {
        a1 = m->r->l[line_index].p[i].first;
        b1 = m->r->l[line_index].p[i].second;
        found_symmetric = false;

        for (int j = 0; j < rel_cardinality; j++)
        {

            if (j == i)
            {
                continue;
            }

            a2 = m->r->l[line_index].p[j].first;
            b2 = m->r->l[line_index].p[j].second;

            if (a2 == b1 && b2 == a1)
            {
                found_symmetric = true;
            }
        }
        if (!found_symmetric){
            printf("false\n");
            return false;
        }
    }
    printf("true\n");
    return true;
}

int transitive(Main *m, int line_index)
{

    int rel_cardinality = m->r->l[line_index].cardinality;
    int a1, b1, a2, b2, c1, c2;
    bool found_transitive;

    for (int i = 0; i < rel_cardinality; i++)
    {
        a1 = m->r->l[line_index].p[i].first;
        b1 = m->r->l[line_index].p[i].second;
        found_transitive = false;

        for (int j = 0; j < rel_cardinality; j++)
        {
            if (j == i)
            {
                continue;
            }
            b2 = m->r->l[line_index].p[j].first;
            if (b2 == b1)
            {
                printf("mala by byt 3 it. a je: %d\n", j);
                c1 = m->r->l[line_index].p[j].second;

                for (int k = 0; k < rel_cardinality; k++)
                {
                    if (k == j)
                    {
                        continue;
                    }
                    a2 = m->r->l[line_index].p[k].first;
                    c2 = m->r->l[line_index].p[k].second;
                    if (a2 == a1 && c2 == c1)
                    {
                        found_transitive = true;
                    }
                }
            }
        }
        if (found_transitive)
        {
            printf("true\n");
            return true;
        }
    }
    printf("false\n");
    return false;
}

// * Funkce vraci zdali je relace funkci
bool is_function(Main *m, int line_index_a)
{
    int i, j;
    bool funkce, zero_found;
    int cardinality = m->r->l[line_index_a].cardinality;
    int *definicni_obor = malloc(sizeof(int) * cardinality);
    for (i = 0; i < cardinality; ++i)
    {

        int x_index = m->r->l[line_index_a].p[i].first;

        for (j = 0; j < cardinality; j++)
        {
            funkce = false;
            int x_index2 = definicni_obor[j];
            if (x_index == 0 && zero_found == false)
            {
                zero_found = true;
                break;
            }

            if (x_index == x_index2 && zero_found == true)
            {
                funkce = true;
                break;
            }
            if (x_index == x_index2)
            {
                funkce = true;
                break;
            }
        }

        if (funkce == true)
        {
            printf("false\n");

            return false;
        }
        definicni_obor[i] = x_index;
    }
    printf("true\n");
    return true;
}

//* Funkce vraci zda-li je relace reflexivni.
bool is_reflexive(Main *m, int line_index_a)
{
    int i, j, k, l, h, f;
    int cardinality = m->r->l[line_index_a].cardinality;
    int *reflex = malloc(sizeof(int) * cardinality);
    int index = 0;

    for (i = 0; i < cardinality; i++)
    {
        int x_index = m->r->l[line_index_a].p[i].first;
        int y_index = m->r->l[line_index_a].p[i].second;

        // printf("%d\n", x_index);
        // printf("%d\n", y_index);
        // printf("%d toto je X index\n", x_index);
        for (j = 0; j < cardinality; j++)
        {

            // printf("%d toto je Y index\n", y_index);
            if (x_index == y_index)
            {
                // printf("shoda\n");

                for (k = 0; k <= index; k++)
                {
                    if (x_index == reflex[k])
                        break;
                    if (k == index)
                    {
                        reflex[index] = x_index;
                        // printf("%d\n", reflex[index]);

                        index++;
                        break;
                    }
                }
                // printf("shoda\n");
                // reflexivity = true;
            }
        }
    }
    for (l = 0; l < cardinality; l++)
    {
        int check = m->r->l[line_index_a].p[l].first;
        int backwards_check = m->r->l[line_index_a].p[l].second;
        // printf("Check int: %d\n", check);
        for (h = 0; h <= index; h++)
        {
            // printf("CISLO DPC :%d\n", h);
            // printf("Index num:%d\n", reflex[h]);

            if (check == reflex[h] && h <= index)
            {
                // printf("Shooda\n");
                break;
            }
            if (check != reflex[h] && h == index)
            {
                printf("false\n");
                free(reflex);
                return false;
            }
        }
        for (f = 0; f <= index; f++)
        {
            if (backwards_check == reflex[f] && f <= index)
            {
                // printf("Shooda\n");
                break;
            }
            if (backwards_check != reflex[h] && f == index)
            {
                printf("false\n");
                free(reflex);
                return false;
            }
        }
    }
    free(reflex);
    printf("true\n");
    return true;
}

//* Funkce vraci zda-li je relace asymetricka.
bool is_asymmetric(Main *m, int line_index_a)
{
    int i, j;
    bool asymmetricity_x;
    int cardinality = m->r->l[line_index_a].cardinality;
    for (i = 0; i < cardinality; i++)
    {
        int x_index = m->r->l[line_index_a].p[i].first;
        int y_index = m->r->l[line_index_a].p[i].second;

        // printf("%d toto je X index\n", x_index);
        for (j = 0; j < cardinality; j++)
        {
            asymmetricity_x = false;
            int x_index2 = m->r->l[line_index_a].p[j].second;
            int y_index2 = m->r->l[line_index_a].p[j].first;

            // printf("%d toto je Y index\n", y_index);
            if (x_index == x_index2 && y_index == y_index2)
            {
                // printf("shoda\n");
                asymmetricity_x = true;
                break;
            }
            if (j < cardinality && (x_index != x_index2 || y_index != y_index2))
            {
                continue;
            }
        }
        if (asymmetricity_x == true)
        {
            printf("false\n");
            return false;
        }
    }

    printf("true\n");
    return true;
}

//! Funkce vraci zda-li je relace tranzitivni.
bool transitivity(Main *m, int line_index_a)
{
    int i, j, k;
    bool transitive;
    int relation_cardinality = m->r->l[line_index_a].cardinality;
    for (i = 0; i < relation_cardinality; i++)
    {
        int first_x_index = m->r->l[line_index_a].p[i].first;
        int first_y_index = m->r->l[line_index_a].p[i].second;

        for (j = 0; j < relation_cardinality; j++)
        {
            int second_x_index = m->r->l[line_index_a].p[j].first;
            int second_y_index = m->r->l[line_index_a].p[j].second;

            transitive = false;
            if (second_x_index == first_y_index && second_y_index == first_x_index)
            {
                transitive = true;
                break;
            }
        }
        if (transitive == false)
            continue;

        for (k = 0; k < relation_cardinality; k++)
        {
            int x_check = m->r->l[line_index_a].p[k].first;
            int y_check = m->r->l[line_index_a].p[k].second;
            if (x_check == first_x_index && y_check == first_x_index)
            {
                break;
            }
            if (k + 1 == relation_cardinality)
            {
                printf("false\n");
                return false;
            }
        }
    }

    printf("true\n");
    return true;
}

void codomain(Main *m, int line_index_a)
{
    int i, j;
    int current_element;
    int index = 0;
    int cardinality = m->r->l[line_index_a].cardinality;
    int *obor_hodnot = malloc(sizeof(int) * cardinality);
    bool shoda;

    for (i = 0; i < cardinality; i++)
    {
        shoda = false;
        // printf("Neco se deje v prvnim cyklu\n");
        current_element = m->r->l[line_index_a].p[i].second;
        for (j = 0; j < index; j++)
        {
            // printf("Neco se deje v druhem cyklu\n");

            if (obor_hodnot[j] == current_element)
            {
                shoda = true;
                break;
            }
        }
        if (shoda == false)
        {
            obor_hodnot[index] = current_element;
            index++;
            continue;
        }
    }
    print_set(m , index, obor_hodnot);
    free(obor_hodnot);
}
// * Tiskne definicni obor.

void domain(Main *m, int line_index_a)
{
    int i, j;
    int current_element;
    int index = 0;
    int cardinality = m->r->l[line_index_a].cardinality;
    int *definicni_obor = malloc(sizeof(int) * cardinality);
    bool shoda;

    for (i = 0; i < cardinality; i++)
    {
        shoda = false;
        // printf("Neco se deje v prvnim cyklu\n");
        current_element = m->r->l[line_index_a].p[i].first;
        for (j = 0; j < index; j++)
        {
            // printf("Neco se deje v druhem cyklu\n");

            if (definicni_obor[j] == current_element)
            {
                shoda = true;
                break;
            }
        }
        if (shoda == false)
        {
            definicni_obor[index] = current_element;
            index++;
            continue;
        }
    }
    print_set(m, index, definicni_obor);

    free(definicni_obor);
}


int injective(Main *m, int rel_line_index, int set_A_line_index, int set_B_line_index){
    int rel_cardinality = m->r->l[rel_line_index].cardinality;
    (void) set_A_line_index;
    //  = m->s->l[set_A_line_index].cardinality;
    (void) set_B_line_index;
    // = m->s->l[set_B_line_index].cardinality;
    int index = 0;
    int match = 0;
    for(index = 0 ; index < rel_cardinality; index++){
        //checks if first is in set A;
        //checks if second is in set B;
        //checks if second is in any other pair;
        for(int j = index; j<rel_cardinality; j++){
            if(m->r->l[rel_line_index].p[index].second == m->r->l[rel_line_index].p[j].second){
                match++;
            }
            if(match < 2){
                printf("false\n");
                return false;
            }
        }
    }
    printf("true\n");
    return true;
}


// int surjective(Main *m, int rel_line_index, int set_A_line_index, int set_B_line_index){

//     return true;
// }

// int bijective(Main *m, int rel_line_index, int set_A_line_index, int set_B_line_index){
//     if(injective(m,rel_line_index,set_A_line_index,set_B_line_index) && surjective(m,rel_line_index,set_A_line_index,set_B_line_index)){
//         return true;
//     }
//     return false;
// }

/**
 * @brief
 *
 * @param m
 * @param element
 * @param idx
 * @return int
 */
int function_call(Main *m, int func_index, int par1, int par2, int par3){
    // printf("p1:%d p2:%d p:3%d\n", par1,par2,par3);
    int rel_1 = rel_find_index(m, par1);
    int set_1 = set_find_index(m,par1);
    int set_2 = set_find_index(m,par2);
    int set_3 = set_find_index(m,par3);
    (void) set_3;
    // printf(" r:%d s1:%d s2:%d s3:%d\n", rel_1,set_1, set_2,set_3);

    // if(par1 == 0 && par2 == 0 && par3 == 0){
    //     fprintf(stderr,"Invalid function syntax\n");
    //     return -1;
    // }
    switch(func_index) {
        case 0 :
            if (set_2 || set_3 != 0)
            is_empty(m,set_1);
            break;
        case 1 :
            printf("%d\n",m->s->l[set_1].cardinality);
            break;
        case 2 :
            do_complement(m,set_1);
            break;
        case 3 :
            is_reflexive(m,rel_1);
            break;
        case 4 :
            symmetric(m,rel_1);
            break;
        case 5 :
            is_asymmetric(m,rel_1);
            break;
        case 6 :
            // transitivity(m,rel_1);
            transitive(m,rel_1);
            break;
        case 7 :
            is_function(m,rel_1);
            break;
        case 8 :
            domain(m,rel_1);
            break;
        case 9 :
            codomain(m,rel_1);
            break;
        case 10 :
            do_union(m,set_1,set_2);
            break;
        case 11 :
            intersect(m,set_1,set_2);
            break;
        case 12 :
            minus(m,set_1,set_2);
            break;
        case 13 :
            if(subseteq(m,set_1,set_2))
                printf("true\n");
            else
                printf("false\n");
            break;
        case 14 :
            subset(m,set_1,set_2);
            break;
        case 15 :
            equals(m,set_1,set_2);
            break;
        case 16 :
            printf("injective params: %d %d %d",rel_1,set_2,set_3);
            break;
        case 17 :
            printf("surjective\n");
            break;
        case 18 :
            printf("bijective\n");
            break;
        default :
            printf("bad func name");
    }
    return true;
}

/**
 * @brief 
 * 
 * @param file 
 * @param savednum 
 * @param character 
 * @return int 
 */
int parse_num(FILE *file, int *savednum, int *character){
    //C command 333333 333 333 333\n
    // char character = getc(file);
    char *ptr;
    int index = 0;
    char number[5];
    strcpy(number,"");
    // printf("number before:%s\n",number);
    while(*character != '\n' && *character != EOF){
            number[index++] = *character;
            *character = getc(file);
            //loads number
            if(*character == ' ' || *character == '\n' || *character == EOF){
                number[index] = '\0';
                // *savednum = atoi(number);
                *savednum = strtol(number,&ptr,10);
                // printf("ptr:%s\n",ptr);
                // printf("savenum:%d\n",*savednum);
                return 1;
            }
    }
    return 0;
}

int function_parser(FILE *file, Main *m){
    char temp[31];
    int index = 0;
    int character = fgetc(file);
    temp[index] = character;
    int func_num = 0;
    int firstnum = 0, secondnum = 0, thirdnum = 0;


    while (character != ' ' && character != '\n'){
        temp[index++] = character;
        // printf("char: %c\n",character);
        character = fgetc(file);
        if (character == ' ')
        {
            temp[index] = '\0';
            // printf("temp: %s\n",temp);
            func_num = find_function_keyword(temp,1);
            if (func_num == -1){
                fprintf(stderr,"Wrong function keyword");
                return -1;
                }
        }
            if(character == '\n'){
                fprintf(stderr,"ERROR: no function input given.\n");
                return -1;
            }
    }
    // TODO check if found function has exact number of parameters

    int num_of_parsed = 0;
    while(character != '\n' && character != EOF){
        character = fgetc(file);
        num_of_parsed +=parse_num(file,&firstnum,&character);
        num_of_parsed +=parse_num(file,&secondnum,&character);
        num_of_parsed +=parse_num(file,&thirdnum,&character);
    }
    if((func_num < 9 && num_of_parsed != 1) || (func_num > 9 && num_of_parsed != 2) || (func_num > 15 && num_of_parsed > 3) || (func_num > 15 && num_of_parsed < 3) ){
        fprintf(stderr,"Function has a wrong number of parameters\n");
        return -1;
    }

    if(function_call(m, func_num, firstnum, secondnum, thirdnum))
        return 0;
    else{
        printf("this return\n");
        return -1;
    }
}

/**
 * @brief
 *
 * @param m
 */
void print_universum(Main *m)
{
    // U -> element -> mezera until last element -> \n
    printf("U ");
    for (int i = 0; i < m->u->universum_cardinality; i++)
    {
        printf("%s", m->u->elements[i].element);
        if (i == m->u->universum_cardinality - 1)
            break;
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
void print_set_old(Main *m){

    int uni_index = 0;
    int line_cardinality = m->s->line_cardinality;

    printf("S");
    for (int i = 0; i < m->s->l[line_cardinality].cardinality; i++)
    {   
        printf(" ");
        uni_index = m->s->l[line_cardinality].set_items[i];
        printf("%s", m->u->elements[uni_index].element);
        if (i == m->s->l[line_cardinality].cardinality - 1)
            break;
    }
    printf("\n");
}

void print_set(Main *m, int cardinality, int *set){
    printf("S");
    for (int i = 0; i < cardinality; i++){
        printf(" ");
        printf("%s", m->u->elements[set[i]].element);
        if(i == cardinality-1)
            break;
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
    // R ->( -> element1 -> mezera -> element2 ->) -> until last pair -> \n
    int rel_index = 0;
    int line_cardinality = m->r->line_cardinality;

    printf("R ");
    for (int i = 0; i < m->r->l[line_cardinality].cardinality; i++){
        rel_index = m->r->l[line_cardinality].p[i].first; // first pair

        printf("(%s ", m->u->elements[rel_index].element);

        rel_index = m->r->l[line_cardinality].p[i].second; //second pair

        printf("%s)", m->u->elements[rel_index].element);
        if (i == m->r->l[line_cardinality].cardinality - 1)
            break;
        printf(" ");
    }
    printf("\n");
}

int relation_line_add(Main *m, int line_index){
    int line_cardinality = m->r->line_cardinality;

    if (m->r->line_cardinality + 1 > m->r->line_capacity)
    {
        m->r->line_capacity = m->r->line_capacity * 2 + 1;
        m->r->l = allocate_or_resize(m->r->l, m->r->line_capacity * sizeof(Relation_line));
        if (m->r->l == NULL){
            fprintf(stderr, "Memory could not be allocated\n");
            return -1;
        }
    }
    m->r->l[line_cardinality].line_index = line_index;
    // set_ctor(line_index);

    return true;
}

int set_line_add(Main *m, int line_index){
    int line_cardinality = m->s->line_cardinality;

    if (m->s->line_cardinality + 1 > m->s->line_capacity){
        m->s->line_capacity = m->s->line_capacity * 2 + 1;
        m->s->l = allocate_or_resize(m->s->l, m->s->line_capacity * sizeof(Set_line));
        if (m->s->l == NULL){
            fprintf(stderr, "Memory could not be allocated\n");
            return -1;
        }
    }
    m->s->l[line_cardinality].line_index = line_index;
    // set_ctor(line_index);

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
// **** FUNCTIONS ************************

int main(int argc, char *argv[]){
    FILE *file;

    // printf("argc:%d argv[%d]: %s\n\n",argc,1,argv[1]);

    if (argc > 2){
        fprintf(stderr, "Only one input is allowed");
        return EXIT_FAILURE;
    }

    char *filename = argv[1];
    int line_index = 1;
    file = fopen(filename, "r");

    if (file == NULL){
        fprintf(stderr, "This file name is invalid");
        fclose(file);
        return -1;
    }

    // init
    Main *m = main_ctor();
    if (m == NULL){
        fclose(file);
        return 1;
    }

    while (1){
        int return_value = type_check(file);
        if (return_value == 2){
            if(load_universum(file, m, line_index) == -1){
                main_dtor(m, 3);
                fclose(file);
                return -1;
            }
            if(is_universum_valid(m) == -1){
                return -1;
            }
            print_universum(m);

        }
        if(return_value == 7){
            uni_add_element(m, "", -1);
            print_universum(m);
            set_line_add(m, line_index);
            set_add_element(m, -1, 0);
            (m->s->line_cardinality)++;

        }
        if (return_value == 3){
            set_line_add(m, line_index);
            if(set_to_index(file, m) == -1){
                main_dtor(m, 3);
                fclose(file);
                return -1;
            }
            print_set_old(m);
            (m->s->line_cardinality)++;
        }
        if (return_value == 8){
            set_line_add(m,line_index);
            set_add_element(m, -1, 0);
            if(!is_set(m)){
                main_dtor(m, 3);
                fclose(file);
                return -1;
            }
            print_set_old(m);
            (m->s->line_cardinality)++;
        }
        if (return_value == 4){
            relation_line_add(m, line_index);
            if((relation_to_index(file, m)) == -1){
                fprintf(stderr,"wrong relation syntax");
                line_index++;
                main_dtor(m, 3);
                fclose(file);
                return EXIT_FAILURE;
            }
            print_relation(m);
            (m->r->line_cardinality)++;
        }
        if(return_value == 9){
            relation_line_add(m,line_index);
            relation_add_element(m,-1,true,0);
            print_relation(m);
            (m->r->line_cardinality)++;
        }
        if (return_value == 5){
            if((function_parser(file, m)) == -1){
                main_dtor(m,3);
                fclose(file);
                return EXIT_FAILURE;
            }

        }

        if (!return_value){
            break;
        }
        if(return_value == -1){
            fprintf(stderr, "Syntax error.");
            main_dtor(m,3);
            fclose(file);
            return EXIT_FAILURE;
        }
        if(return_value != 5)
            line_index++;
    }

    main_dtor(m, 3);
    fclose(file);
    return 0;
}