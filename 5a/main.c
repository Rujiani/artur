#include <stdio.h>
#include <stdlib.h>
#include "dialog.h"
#include "array.h"

int main() {
    Array arr;
    arr.ptr = NULL;
    arr.size = 0;

    int menu_choice = 0;
    while (menu(&menu_choice) != -1) {
        int err = 0;
        switch (menu_choice) {
            case 1:
                err = array_input(&arr);
                break;
            case 2:
                err = array_output(&arr);
                break;
            case 3:
                err = array_sort(&arr);
                break;
            case 4:
                printf("Exiting...\n");
                if (arr.ptr) {
                    for (int i = 0; i < arr.size; i++) {
                        free(arr.ptr[i].full_name);
                        free(arr.ptr[i].number);
                    }
                    free(arr.ptr);
                }
                return 0;
            default:
                printf("Unknown menu option. Try again.\n");
                continue;
        }
        if (err == -1) {
            // -1 means EOF or user exit
            printf("Exiting...\n");
            if (arr.ptr) {
                for (int i = 0; i < arr.size; i++) {
                    free(arr.ptr[i].full_name);
                    free(arr.ptr[i].number);
                }
                free(arr.ptr);
            }
            return 0;
        } else if (err != 0) {
            printf("Operation error.\n");
        }
    }

    printf("Exiting...\n");
    if (arr.ptr) {
        for (int i = 0; i < arr.size; i++) {
            free(arr.ptr[i].full_name);
            free(arr.ptr[i].number);
        }
        free(arr.ptr);
    }
    return 0;
}
