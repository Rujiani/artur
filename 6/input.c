#include "input.h"
#include <stdio.h>

int getInt(int *num) {
    // Try to read an integer
    int result = scanf("%d", num);

    // Check scanf result
    if (result == EOF) {
        return -1; // End of file
    } else if (result == 0) {
        while (getchar() != '\n'); // Clear invalid input
        return 1; // Format error
    }
    return 0; // Success
}
