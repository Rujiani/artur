#include <stdio.h>
#include "list.h"
#include "input.h"

#define CHECK_ERROR(err) \
    if (err == 1) { \
        printf("Memory error\n"); \
        break; \
    } \


int msg(Node **list){
    printf("Input line:\n");
    return input_List(list);
}

int main(){
    Node *first_list = NULL, *second_list = NULL;
    int err;
    while((err = msg(&first_list))){
        CHECK_ERROR(err);

        int N, rc;
        printf("Input N:\n");
        while ((rc = getInt(&N)) != -1) {
            if (rc == 1) {
                printf("Wrong format. Try again.\n");
                continue;
            } else {
                int leftover;
                while ((leftover = getchar()) != '\n' && leftover != EOF) {}
                break;
            }
        }

        err = break_The_Words(&first_list, &second_list, N);

        CHECK_ERROR(err);

        printf("First list:\n");
        print_List(first_list);
        printf("Result list:\n");
        print_List(second_list);

        free_List(&first_list);
        free_List(&second_list);
    }
    free_List(&first_list);
    free_List(&second_list);
    return err;
}