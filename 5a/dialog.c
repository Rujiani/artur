#include "dialog.h"
#include "input.h"
#include <stdio.h>

// Display main menu and read user choice
int menu(int *choice){
    printf("\n------ MENU ------\n");
    printf("1. Read array\n");
    printf("2. Write array\n");
    printf("3. Sort array\n");
    printf("4. Exit\n");
    printf("Enter your choice: ");

    int err;
    while((err = getInt(choice)) != 0){
        if(err == -1){
            return -1; 
        }
        printf("Invalid input. Try again: ");
    }
    return 0;
}

// Handle array input
int array_input(Array *arr){
    printf("Select input method:\n");
    printf("1. From stdin\n");
    printf("2. From text file\n");
    printf("3. From binary file\n");
    printf("Your choice: ");

    int m, err = getInt(&m);
    if (err) {
        if(err == -1) return -1;
        return 1;
    }

    switch(m) {
        case 1:
            if (array_read_stdin(arr) != 0) {
                printf("Error reading from stdin.\n");
                return 1;
            }
            break;
        case 2: {
            char fname[256];
            printf("Enter filename: ");
            if (scanf("%255s", fname) != 1) {
                printf("Error reading filename.\n");
                return 1;
            }
            if (array_read_text(arr, fname) != 0) {
                printf("Error reading from text file.\n");
                return 1;
            }
            break;
        }
        case 3: {
            char fname[256];
            printf("Enter filename: ");
            if (scanf("%255s", fname) != 1) {
                printf("Error reading filename.\n");
                return 1;
            }
            if (array_read_bin(arr, fname) != 0) {
                printf("Error reading from binary file.\n");
                return 1;
            }
            break;
        }
        default:
            printf("Unknown input method.\n");
            return 1;
    }
    return 0;
}

// Handle array output
int array_output(const Array *arr){
    if (!arr || !arr->ptr || arr->size <= 0) {
        printf("Array is empty or not initialized.\n");
        return 1;
    }

    printf("Select output method:\n");
    printf("1. To stdout\n");
    printf("2. To text file\n");
    printf("3. To binary file\n");
    printf("Your choice: ");

    int m, err = getInt(&m);
    if (err) {
        if(err == -1) return -1;
        return 1;
    }

    switch(m) {
        case 1:
            if (array_write_stdout(arr) != 0) {
                printf("Error writing to stdout.\n");
                return 1;
            }
            break;
        case 2: {
            char fname[256];
            printf("Enter filename: ");
            if (scanf("%255s", fname) != 1) {
                printf("Error reading filename.\n");
                return 1;
            }
            if (array_write_text(arr, fname) != 0) {
                printf("Error writing to text file.\n");
                return 1;
            }
            break;
        }
        case 3: {
            char fname[256];
            printf("Enter filename: ");
            if (scanf("%255s", fname) != 1) {
                printf("Error reading filename.\n");
                return 1;
            }
            if (array_write_bin(arr, fname) != 0) {
                printf("Error writing to binary file.\n");
                return 1;
            }
            break;
        }
        default:
            printf("Unknown output method.\n");
            return 1;
    }
    return 0;
}

// Handle array sorting
int array_sort(Array *arr){
    if (!arr || !arr->ptr || arr->size <= 0) {
        printf("Array is empty or not initialized.\n");
        return 1;
    }

    printf("Select field to sort by:\n");
    printf("1. Full name\n");
    printf("2. Number\n");
    printf("3. Last call time\n");
    printf("Your choice: ");
    int field;
    if (getInt(&field) != 0 || field < 1 || field > 3) {
        printf("Invalid field.\n");
        return 1;
    }

    printf("Select direction:\n");
    printf("1. Ascending\n");
    printf("2. Descending\n");
    printf("Your choice: ");
    int direction;
    if (getInt(&direction) != 0 || (direction != 1 && direction != 2)) {
        printf("Invalid direction.\n");
        return 1;
    }

    array_qsort(arr, field, direction);
    printf("Array sorted.\n");
    return 0;
}
