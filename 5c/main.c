#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include "gen.h"
#include "sort.h"

static void copy_array(const Sub *src, Sub *dst, int size) {
    // We must duplicate strings
    for (int i = 0; i < size; i++) {
        // copy struct
        dst[i].last_call_time = src[i].last_call_time;
        // deep copy strings
        dst[i].full_name = strdup(src[i].full_name);
        dst[i].number = strdup(src[i].number);
    }
}

static void free_array(Sub *arr, int size) {
    if (!arr) return;
    for (int i = 0; i < size; i++) {
        free(arr[i].full_name);
        free(arr[i].number);
    }
    free(arr);
}

int main() {
    srand((unsigned)time(NULL));

    int field, direction;
    printf("Select field:\n");
    printf("1. Full name\n");
    printf("2. Number\n");
    printf("3. Last call time\n");
    printf("Your choice: ");
    scanf("%d", &field);

    printf("Select direction:\n");
    printf("1. Ascending\n");
    printf("2. Descending\n");
    printf("Your choice: ");
    scanf("%d", &direction);

    int M;
    printf("How many different array sizes to test? ");
    scanf("%d", &M);

    // We'll measure CPU time using clock().
    // For a more accurate measure, consider gettimeofday or clock_gettime if available.

    for (int i = 0; i < M; i++) {
        printf("\n=== Test #%d ===\n", i+1);
        int arr_size;
        printf("Enter array size: ");
        scanf("%d", &arr_size);
        if (arr_size <= 0) {
            printf("Invalid array size.\n");
            continue;
        }
        int R;
        printf("How many repeats for this size? ");
        scanf("%d", &R);
        if (R <= 0) {
            printf("Invalid repeat count.\n");
            continue;
        }

        // We'll accumulate times to compute average
        double total_qsort = 0.0;
        double total_bubble = 0.0;
        double total_pair = 0.0;

        for (int rep = 0; rep < R; rep++) {
            // 1) Generate random array
            Sub* original = generate_sub_array(arr_size);

            // 2) Make copies for each algorithm
            Sub* arr_qsort = (Sub*)malloc(arr_size * sizeof(Sub));
            Sub* arr_bubble = (Sub*)malloc(arr_size * sizeof(Sub));
            Sub* arr_pair = (Sub*)malloc(arr_size * sizeof(Sub));

            copy_array(original, arr_qsort, arr_size);
            copy_array(original, arr_bubble, arr_size);
            copy_array(original, arr_pair, arr_size);

            // 3) Measure qsort
            clock_t start = clock();
            sort_sub_array(arr_qsort, arr_size, 1, field, direction);
            clock_t end = clock();
            double elapsed_qsort = (double)(end - start) / CLOCKS_PER_SEC;

            // 4) Measure bubble
            start = clock();
            sort_sub_array(arr_bubble, arr_size, 2, field, direction);
            end = clock();
            double elapsed_bubble = (double)(end - start) / CLOCKS_PER_SEC;

            // 5) Measure pair insertion
            start = clock();
            sort_sub_array(arr_pair, arr_size, 3, field, direction);
            end = clock();
            double elapsed_pair = (double)(end - start) / CLOCKS_PER_SEC;

            total_qsort += elapsed_qsort;
            total_bubble += elapsed_bubble;
            total_pair += elapsed_pair;

            // free everything
            free_sub_array(original, arr_size);
            free_array(arr_qsort, arr_size);
            free_array(arr_bubble, arr_size);
            free_array(arr_pair, arr_size);
        }

        // compute average
        double avg_qsort = total_qsort / R;
        double avg_bubble = total_bubble / R;
        double avg_pair = total_pair / R;

        // Output data
        // Times are in seconds, you can convert to milliseconds or microseconds
        printf("Array size = %d, repeats = %d\n", arr_size, R);
        printf("Avg time (qsort)         = %.6f sec\n", avg_qsort);
        printf("Avg time (bubble sort)   = %.6f sec\n", avg_bubble);
        printf("Avg time (pair insert)   = %.6f sec\n", avg_pair);
    }

    printf("\nDone.\n");
    return 0;
}
