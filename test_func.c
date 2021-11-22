#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>


void set_print(int size, int *array){
    printf("S ");
    for (int i = 0; i < size; i++){
        printf("%d ",array[i]);
    }
    printf("\n");

// [5,0,4]
}

//1. prints true if set is empty, otherwise prints false.
bool is_empty(int cardinality){
    return cardinality>0 ? false : true;
}

//2. ...

//3. outputs complement of a set(in relation with universe)
// toto som robil s tym ze to funguje na setcal.c, kde mame universe ulozeny ako ({index, element}, {index, elemement}...) 
// void do_complement(char *universe, int universe_cardinality, int *set, int set_cardinality){
//     bool found;
    
//     printf("S ");
//     for (int i = 0; i < universe_cardinality; i++){
//         found = false;
//         for (int j = 0; j < set_cardinality; j++){
//             if (set[j] == i)
//                 found = true;
//         }
//         if (!found)
//             printf("%s ", universe[i]);
//     }
//     printf("\n");
// }

//4.. Outputs a union of two sets.
void do_union(int *array_a, int cardinality_A, int * array_b, int cardinality_B){
    bool in_union;
    int *union_set = malloc((cardinality_A+cardinality_B)*sizeof(int)); //creates a temp array of a maximum union of the two arrays.
    int i;
    int union_cardinality = 0;
    for(i = 0; i < cardinality_A; i++){
        union_set[i] = array_a[i];
        union_cardinality++;
    }
    for(int j = 0; j < cardinality_B; j++){
        in_union = false;
        for(int k = 0; k < union_cardinality; k++){
            if(array_b[j] == union_set[k]){
                in_union = true;
            }
        }
        if(!in_union){
            printf("i: %d\n",i);
            union_set[i] = array_b[j];
            union_cardinality++;
            i++;
        }
    }
    set_print(union_cardinality,union_set);
    free(union_set);

}

//5. ...

//6. prints A-B
void minus(int *array_A, int cardinality_A, int *array_B, int cardinality_B){
    //todo, ak sa element z A nenachadza v B, mozem ho printit... that is all folks
    // dost sa mi algoritmus podoba na subseteq forsomreason to asi je to iste haha, ak !found tak printim a done
    bool element_found;
    int *difference = malloc(cardinality_A*sizeof(int));
    int diff_idx = 0;
    
    for (int i = 0; i < cardinality_A; i++){
        element_found = false;
        for (int j = 0; j < cardinality_B; j++){
            if(array_A[i] == array_B[j]){
                element_found = true;
                break;
            }
        }
        if (!element_found){
            difference[diff_idx] = array_A[i];
            diff_idx++;
        }
    }
    set_print(diff_idx, difference);
    free(difference);
}

//7. returns true if set A is subset of set B, otherwise returns false.
//REWORK algorithm
bool subseteq(int *array_A, int cardinality_A, int *array_B, int cardinality_B){
    // [3,4]
    // [1,2,3,4,5,6,7]
    bool element_found;
    for(int i = 0; i < cardinality_A; i++){
        element_found = false;
        for(int j = 0; j < cardinality_B; j++){
            if(array_A[i] == array_B[j]){
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

//8. returns true if set A is vlastna subset of set B
bool subset(int *array_A, int cardinality_A, int *array_B, int cardinality_B){
    if (subseteq(array_A, cardinality_A, array_B, cardinality_B) == true && cardinality_A < cardinality_B)
        return true;
    return false;
}

//9. returns true if set A is equal to set B
int compare(const void * a, const void * b) {
   return ( *(int*)a - *(int*)b );
}
bool equals(int *array_A, int cardinality_A, int *array_B, int cardinality_B){
//https://www.cplusplus.com/reference/cstring/memcmp/
//https://www.cplusplus.com/reference/cstdlib/qsort/
    if (cardinality_A != cardinality_B)
        return false;

    qsort(array_A, cardinality_A, sizeof(int), compare); //tato funkce zmeni hodnoty v Set *s!!! snad to neni problem...
    qsort(array_B, cardinality_B, sizeof(int), compare);
    
    if (memcmp(array_A, array_B, cardinality_A*sizeof(int)) == 0)
        return true;
    return false;
}


int main(int argc, char *argv[]){
    printf("argc: %d , argv: %s\n",argc, argv[0]);

    //int universe[10] = {1,2,3,4,5,6,7,8,9,10};
    int array_a[10] = {1,2,3,5,6,7,8};
    int array_b[4] = {1,2,3,4};
    int array_c[4] = {6,2,4,1};
    int array_d[5] = {1,3,4,2,5};
    int array_e[4] = {4,2,3,1};
    int cardinality = 0;

    printf("\nfunction 1 is_empty:\n");
    printf("is empty: %d\n\n",is_empty(cardinality));

    // printf("function 2 do_complement:\n");
    // set_print(10, universe);
    // set_print(4,array_c);
    // printf("complement:\n");
    // do_complement(universe,10,array_c,4);
    // printf("\n");

    printf("bool subseteq array_c and array_d: %d\n",subseteq(array_b,4,array_d,5));
    printf("bool subseteq array_d and array_c: %d\n", subseteq(array_d, 5, array_c, 4));

    printf("\nArray_B - Array_C:\n");
    minus(array_b, 4, array_c, 4);

    
    do_union(array_a,7,array_b,4);

    printf("\nequals:\n");
    printf("array_b equals array_c: %d\n", equals(array_b, 4, array_c, 4));
    printf("array_e equals array_b: %d\n", equals(array_e, 4, array_b, 4));
    return 0;
}