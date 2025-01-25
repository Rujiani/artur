#include <stdio.h>
#include "dialog.h"
#include <stdlib.h>

int main(){
    int menu_choice = 0, error = 0;
    Array array;
    while(menu(&menu_choice) != -1){
        switch (menu_choice) {
            case 1:
                error = array_initialization(&array);
            break;
            case 2:
                error = array_change_memory_size(&array);
            break;
            case 3:
                error = array_insert_el(&array);
            break;
            case 4:
                error = array_delete_el(&array);
            break;
            case 5:
                array_subsequence_stuff(&array);
            break;
            case 6:
                array_print(&array);
                continue;
            default:
                printf("Unknown menu option. Try again.\n");
                continue;
        }

        switch (error) {
            case 1:
                printf("Input error\n");
            break;
            case 2:
                printf("Memory error\n");
                free(array.ptr);
                return 1;
            break;
            case 3:
                printf("Size error\n");
            break;
            case -1:
                printf("Exiting...\n");
                free(array.ptr);
                return 0;
            default:
                array_print(&array);
            break;
        }
    }
    printf("Exiting...\n");
    free(array.ptr);
    return 0;
}