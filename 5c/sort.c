#include "sort.h"
#include <string.h>
#include <stdlib.h>


int (*select_cmp(int field, int direction))(const void*, const void*) {
    // field: 1-full_name,2-number,3-time
    // direction: 1-asc,2-desc
    if (field == 1) {
        return (direction == 1) ? cmp_full_name_asc : cmp_full_name_desc;
    } else if (field == 2) {
        return (direction == 1) ? cmp_number_asc : cmp_number_desc;
    } else {
        return (direction == 1) ? cmp_time_asc : cmp_time_desc;
    }
}

// Bubble
void bubble_sort(void *base, size_t n, size_t size, int (*cmp)(const void*, const void*)) {
    char *arr = (char*)base;
    for (size_t i = 0; i < n - 1; i++) {
        for (size_t j = 0; j < n - 1 - i; j++) {
            void *p1 = arr + j * size;
            void *p2 = arr + (j + 1) * size;
            if (cmp(p1, p2) > 0) {
                char tmp[256];
                memcpy(tmp, p1, size);
                memcpy(p1, p2, size);
                memcpy(p2, tmp, size);
            }
        }
    }
}

// Pair insertion
void pair_insertion_sort(void *base, size_t n, size_t size,
                         int (*cmp)(const void*, const void*)) {
    char *a = (char*)base;
    size_t i = 0;

    while (i + 1 < n) {
        char X[256], Y[256];
        memcpy(X, a + i * size, size);
        memcpy(Y, a + (i + 1) * size, size);

        // Make sure X >= Y
        if (cmp(X, Y) < 0) {
            char tmp[256];
            memcpy(tmp, X, size);
            memcpy(X, Y, size);
            memcpy(Y, tmp, size);
        }
        int j = (int)i - 1;
        // Insert X
        while (j >= 0 && cmp(a + j*size, X) > 0) {
            memcpy(a + (j+2)*size, a + j*size, size);
            j--;
        }
        memcpy(a + (j+2)*size, X, size);

        // Insert Y
        while (j >= 0 && cmp(a + j*size, Y) > 0) {
            memcpy(a + (j+1)*size, a + j*size, size);
            j--;
        }
        memcpy(a + (j+1)*size, Y, size);

        i += 2;
    }

    // If odd
    if (i < n) {
        char last[256];
        memcpy(last, a + i*size, size);
        int j = (int)i - 1;
        while (j >= 0 && cmp(a + j*size, last) > 0) {
            memcpy(a + (j+1)*size, a + j*size, size);
            j--;
        }
        memcpy(a + (j+1)*size, last, size);
    }
}

// High-level
void sort_sub_array(Sub *arr, int size, int algo, int field, int direction) {
    if (!arr || size <= 1) return;
    int (*cmp)(const void*, const void*) = select_cmp(field, direction);
    if (!cmp) return;

    switch (algo) {
        case 1:
            qsort(arr, size, sizeof(Sub), cmp);
            break;
        case 2:
            bubble_sort(arr, size, sizeof(Sub), cmp);
            break;
        case 3:
            pair_insertion_sort(arr, size, sizeof(Sub), cmp);
            break;
        default:
            break;
    }
}
