#include "dialog.h"
#include "array.h"
#include "input.h"
#include <stdio.h>

int menu(int *num){
    printf("1. Array initialization\n");
    printf("2. Change memory size\n");
    printf("3. Insert element\n");
    printf("4. Delete element\n");
    printf("5. Subsequence operations\n");
    printf("6. Print array\n");
    int err;
    while((err = getInt(num)) != 0){
        if(err == -1){
            return -1;
        }
        printf("Error of input, try again.\n");
    }
    return 0;
}

int array_initialization(Array *arr){
    printf("Enter size of array\n");
    int size, err = getInt(&size);
    if(err){
        return err;
    }
    return create_new_array(arr, size);;
}

int array_change_memory_size(Array *arr){
    printf("Enter new size of array\n");
    int size, err = getInt(&size);
    if(err){
        return err;
    }
    return change_size(arr, size);;
}

int array_insert_el(Array *arr){
    printf("Enter index of array\n");
    int index, element, err = getInt(&index);
    if(err){
        return err;
    }
    printf("Enter new element\n");
    err = getInt(&element);
    if(err){
        return err;
    }
    return add_element(arr, index, element);
}

int array_delete_el(Array *arr){
    printf("Enter index of array\n");
    int index, err = getInt(&index);
    if(err){
        return err;
    }
    return delete_element(arr, index);
}

void array_subsequence_stuff(Array *arr){
    subsequence_stuff(arr);
}

void array_print(Array *arr){
    print(arr);
}