#include "input.h"
#include <stdio.h>

int getInt(int *value) {
    if (!value) return 1;
    int ret = scanf("%d", value);
    if (ret == EOF) {
        return -1; // EOF or exit
    } else if (ret != 1) {
        int c;
        while ((c = getchar()) != '\n' && c != EOF) {}
        return 1;  // invalid input
    }
    return 0;
}
