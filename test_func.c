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

//prints true if set is empty, otherwise prints false.
bool is_empty(int cardinality){
    return cardinality>0 ? false : true;
}

//Outputs a union of two sets.
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

//returns true if set A is subset of set B, otherwise returns false.
//REWORK algorithm
bool subseteq(int *array_A, int cardinality_A, int *array_B, int cardinality_B){
    // [1,2]
    // [1,2,3,4,5,6,7]
    for(int i = 0; i < cardinality_A; i++){
        for(int j = 0; j < cardinality_B; j++){
            if(array_A[i] == array_B[j]){
                //element in set was found in set B

            }
            else{
                //element was not found in set B. Hence, set A is not a subset of set B.
                return false;
            }
        }
    }
    return true;
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