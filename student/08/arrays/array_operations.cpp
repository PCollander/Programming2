#include "array_operations.hh"
#define ARRAY_OPERATIONS_HH

void reverse(int* leftptr, int* rightptr){
    int tmp;
    --rightptr;
    while(leftptr<rightptr){
        tmp = *rightptr;
        *rightptr = *leftptr;
        *leftptr = tmp;
        ++leftptr;
        --rightptr;
    }
}

void copy(int* itemptr, int* endptr, int* targetptr){
    while(itemptr != endptr){
        *targetptr = *itemptr;
        ++ targetptr;
        ++ itemptr;
    }
}

int greatest_v2(int* itemptr, int* endptr){
    int greatest = *itemptr;
    while(itemptr != endptr){
        if(greatest < *itemptr){
            greatest = *itemptr;
        }
        ++ itemptr;
    }
    return greatest;
}

int greatest_v1(int* itemptr, int size){
    int greatest = *itemptr;
    for (int i=0; i < size; ++i){
        if (greatest < *itemptr){
            greatest = *itemptr;
        }
        ++itemptr;
    }
    return greatest;
}
