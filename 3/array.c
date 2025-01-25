#include "array.h"
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

bool is_even(int num){
    return !(num % 2);
}

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
    int w = 0; // write index
    for(int i = 0; i < arr->size;){
        int sum = arr->ptr[i]; // take the first element
        int parity = arr->ptr[i] % 2;
        int j = i + 1; // next element index

        // accumulate while parity is the same
        while(j < arr->size && (arr->ptr[j] % 2) == parity){
            sum += arr->ptr[j];
            j++;
        }

        // if we have at least 2 elements with the same parity
        if((j - i) >= 2){
            arr->ptr[w++] = sum;
        } else {
            // if only one element, copy it
            arr->ptr[w++] = arr->ptr[i];
        }
        i = j; // skip to the next segment
    }
    arr->size = w; // update the array size
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