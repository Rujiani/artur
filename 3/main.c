#include <stdio.h>
#include "dialog.h"

int main(){
    int menu_choice = 0, error = 0;
    Array array;
    while((menu_choice = menu())){
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
            break;
            default:
                printf("Unknown menu option. Try again.\n");
                continue;
        }

        switch (error) {
            case 1:
                printf("Memory error\n");
            break;
            case 2:
                printf("Input error\n");
            break;
            case 3:
                printf("Size error\n");
            break;
            case -1:
                printf("Exiting...\n");
                return 0;
            default:
                array_print(&array);
            break;
        }
    }
}