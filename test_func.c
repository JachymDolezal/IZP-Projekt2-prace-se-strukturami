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
void do_complement(char *universe, int universe_cardinality, int *set, int set_cardinality){
    bool found;
    
    printf("S ");
    for (int i = 0; i < universe_cardinality; i++){
        found = false;
        for (int j = 0; j < set_cardinality; j++){
            if (set[j] == i)
                found = true;
        }
        if (!found)
            printf("%s ", universe[i]);
    }
}

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
    int difference = malloc(cardinality_A*sizeof(int));
    int diff_idx = 0;
    
    for (int i = 0; i < cardinality_A; i++){
        element_found = false;
        for (int j = 0; j < cardinality_B; j++){
            if(array_A[i] == array_B[j]){
                element_found = true;
                break;
            }
            if (!element_found)
                difference[diff_idx] = array_A[i];
                diff_idx++;
        }
    }
    set_print(diff_idx+1, difference);
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

    int array_a[10] = {1,2,3,5,6,7,8,4};
    int array_b[10] = {1,2,3,4};
    int cardinality = 0;

    printf("is empty: %d\n",is_empty(cardinality));

    printf("bool subsetqt: %d\n",subseteq(array_a,4,array_b,4));

    do_union(array_a,8,array_b,4);

    return 0;
}