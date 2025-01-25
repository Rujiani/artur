#include "array.h"
#include <stdlib.h>
#include <stdio.h>

int create_new_array(Array *arr, int size){
    int *temp_ptr = (int*)calloc(size, sizeof(int));
    if(temp_ptr == NULL){
        return 2;
    }
    arr->ptr = temp_ptr;
    arr->size = 0;
    arr->reserved = size;
    return 0;
}

int change_size(Array *arr, int size){
    int *temp_ptr = realloc(arr->ptr, size * sizeof(int));
    if(temp_ptr == NULL){
        return 2;
    }
    arr->ptr = temp_ptr;
    arr->reserved = size;
    return 0;
}

int add_element(Array *arr, int index, int element){
    if(index >= arr->reserved || arr->size == arr->reserved){
        return 3;   //size error
    }
    if(index >= arr->size){
        arr->ptr[arr->size++] = element;
    }
    else{
        for(int i = arr->size; i > index; --i){
            arr->ptr[i] = arr->ptr[i - 1];
        }
        arr->ptr[index] = element;
        arr->size++;
    }
    return 0;
}

int delete_element(Array *arr, int index){
    if(index >= arr->size){
        return 3;
    }
    for(int i = index; i < arr->size - 1; i++){
        arr->ptr[i] = arr->ptr[i + 1];
    }
    arr->size--;
    return 0;
}

void subsequence_stuff(Array *arr){
}

void print(Array *arr){
    for(int i = 0; i < arr->size; ++i){
        if(i){
            printf(", ");
        }
        printf("%d", arr->ptr[i]);
    }
    printf("\nSize: %d, Reserved size: %d\n", arr->size, arr->reserved);
}