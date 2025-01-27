#include "array.h"
#include "subscriber.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Free old data in the array
static void free_array_data(Array *arr) {
    if (!arr || !arr->ptr) return;
    for (int i = 0; i < arr->size; i++) {
        free(arr->ptr[i].full_name);
        free(arr->ptr[i].number);
    }
    free(arr->ptr);
    arr->ptr = NULL;
    arr->size = 0;
}

// Read from stdin
int array_read_stdin(Array *arr) {
    if (!arr) return -1;

    printf("Enter number of subscribers: ");
    int n;
    if (scanf("%d", &n) != 1 || n <= 0) {
        return -1;
    }

    // Считываем перевод строки, оставшийся после scanf("%d", ...)
    getchar();

    free_array_data(arr);

    arr->ptr = (Sub*)malloc(n * sizeof(Sub));
    if (!arr->ptr) {
        return -1;
    }
    arr->size = n;

    for (int i = 0; i < n; i++) {
        char buf_name[256];
        char buf_number[256];
        int time_val;

        printf("Subscriber %d:\n", i + 1);

        printf("  Full name: ");
        if (scanf(" %[^\n]", buf_name) != 1) {
            return -1;
        }
        // \n
        getchar();

        printf("  Number: ");
        if (scanf(" %[^\n]", buf_number) != 1) {
            return -1;
        }
        getchar();

        printf("  Last call time: ");
        if (scanf("%d", &time_val) != 1) {
            return -1;
        }
        //\n
        getchar();

        arr->ptr[i].full_name = strdup(buf_name);
        arr->ptr[i].number = strdup(buf_number);
        arr->ptr[i].last_call_time = time_val;
    }

    return 0;
}

// Read from text file
int array_read_text(Array *arr, const char *filename) {
    if (!arr || !filename) return -1;
    FILE *f = fopen(filename, "r");
    if (!f) {
        perror("fopen");
        return -1;
    }

    int n;
    if (fscanf(f, "%d", &n) != 1 || n <= 0) {
        fclose(f);
        return -1;
    }

    free_array_data(arr);
    arr->ptr = (Sub*)malloc(n * sizeof(Sub));
    if (!arr->ptr) {
        fclose(f);
        return -1;
    }
    arr->size = n;

    for (int i = 0; i < n; i++) {
        char buf_name[256];
        char buf_number[64];
        int time_val;

        if (fscanf(f, "%255s %63s %d", buf_name, buf_number, &time_val) != 3) {
            fclose(f);
            return -1;
        }

        arr->ptr[i].full_name = strdup(buf_name);
        arr->ptr[i].number = strdup(buf_number);
        arr->ptr[i].last_call_time = time_val;
    }

    fclose(f);
    return 0;
}

// Read from binary file
int array_read_bin(Array *arr, const char *filename) {
    if (!arr || !filename) return -1;
    FILE *f = fopen(filename, "rb");
    if (!f) {
        perror("fopen");
        return -1;
    }

    int n;
    if (fread(&n, sizeof(int), 1, f) != 1 || n <= 0) {
        fclose(f);
        return -1;
    }

    free_array_data(arr);
    arr->ptr = (Sub*)malloc(n * sizeof(Sub));
    if (!arr->ptr) {
        fclose(f);
        return -1;
    }
    arr->size = n;

    for (int i = 0; i < n; i++) {
        int len_name;
        if (fread(&len_name, sizeof(int), 1, f) != 1) {
            fclose(f);
            return -1;
        }
        char *fullname = (char*)malloc(len_name + 1);
        if (!fullname) {
            fclose(f);
            return -1;
        }
        if (fread(fullname, 1, len_name, f) != (size_t)len_name) {
            free(fullname);
            fclose(f);
            return -1;
        }
        fullname[len_name] = '\0';

        int len_number;
        if (fread(&len_number, sizeof(int), 1, f) != 1) {
            free(fullname);
            fclose(f);
            return -1;
        }
        char *number = (char*)malloc(len_number + 1);
        if (!number) {
            free(fullname);
            fclose(f);
            return -1;
        }
        if (fread(number, 1, len_number, f) != (size_t)len_number) {
            free(fullname);
            free(number);
            fclose(f);
            return -1;
        }
        number[len_number] = '\0';

        int time_val;
        if (fread(&time_val, sizeof(int), 1, f) != 1) {
            free(fullname);
            free(number);
            fclose(f);
            return -1;
        }

        arr->ptr[i].full_name = fullname;
        arr->ptr[i].number = number;
        arr->ptr[i].last_call_time = time_val;
    }

    fclose(f);
    return 0;
}

// Write array to stdout
int array_write_stdout(const Array *arr) {
    if (!arr || !arr->ptr) return -1;
    printf("Number of subscribers: %d\n", arr->size);
    for (int i = 0; i < arr->size; i++) {
        printf("[%d] ", i + 1);
        sub_print(&arr->ptr[i]);
        printf("\n");
    }
    return 0;
}

// Write array to text file
int array_write_text(const Array *arr, const char *filename) {
    if (!arr || !filename || !arr->ptr) return -1;
    FILE *f = fopen(filename, "w");
    if (!f) {
        perror("fopen");
        return -1;
    }

    fprintf(f, "%d\n", arr->size);
    for (int i = 0; i < arr->size; i++) {
        fprintf(f, "%s %s %d\n",
                arr->ptr[i].full_name,
                arr->ptr[i].number,
                arr->ptr[i].last_call_time);
    }
    fclose(f);
    return 0;
}

// Write array to binary file
int array_write_bin(const Array *arr, const char *filename) {
    if (!arr || !filename || !arr->ptr) return -1;
    FILE *f = fopen(filename, "wb");
    if (!f) {
        perror("fopen");
        return -1;
    }

    if (fwrite(&arr->size, sizeof(int), 1, f) != 1) {
        fclose(f);
        return -1;
    }

    for (int i = 0; i < arr->size; i++) {
        int len_name = (int)strlen(arr->ptr[i].full_name);
        if (fwrite(&len_name, sizeof(int), 1, f) != 1) {
            fclose(f);
            return -1;
        }
        if (fwrite(arr->ptr[i].full_name, 1, len_name, f) != (size_t)len_name) {
            fclose(f);
            return -1;
        }

        int len_number = (int)strlen(arr->ptr[i].number);
        if (fwrite(&len_number, sizeof(int), 1, f) != 1) {
            fclose(f);
            return -1;
        }
        if (fwrite(arr->ptr[i].number, 1, len_number, f) != (size_t)len_number) {
            fclose(f);
            return -1;
        }

        if (fwrite(&arr->ptr[i].last_call_time, sizeof(int), 1, f) != 1) {
            fclose(f);
            return -1;
        }
    }

    fclose(f);
    return 0;
}

// Adapting our existing comparators to qsort is optional. 
// We'll do direct selection inside array_qsort with local static cmp.

// Local static comparators for qsort
static int cmp_full_name_asc(const void *a, const void *b) {
    const Sub *s1 = (const Sub*)a;
    const Sub *s2 = (const Sub*)b;
    return strcmp(s1->full_name, s2->full_name);
}
static int cmp_full_name_desc(const void *a, const void *b) {
    const Sub *s1 = (const Sub*)a;
    const Sub *s2 = (const Sub*)b;
    return strcmp(s2->full_name, s1->full_name);
}
static int cmp_number_asc(const void *a, const void *b) {
    const Sub *s1 = (const Sub*)a;
    const Sub *s2 = (const Sub*)b;
    return strcmp(s1->number, s2->number);
}
static int cmp_number_desc(const void *a, const void *b) {
    const Sub *s1 = (const Sub*)a;
    const Sub *s2 = (const Sub*)b;
    return strcmp(s2->number, s1->number);
}
static int cmp_time_asc(const void *a, const void *b) {
    const Sub *s1 = (const Sub*)a;
    const Sub *s2 = (const Sub*)b;
    return s1->last_call_time - s2->last_call_time;
}
static int cmp_time_desc(const void *a, const void *b) {
    const Sub *s1 = (const Sub*)a;
    const Sub *s2 = (const Sub*)b;
    return s2->last_call_time - s1->last_call_time;
}

// Sort with qsort
void array_qsort(Array *arr, int field, int direction) {
    if (!arr || arr->size <= 1) return;

    int (*cmp)(const void *, const void *) = NULL;

    switch (field) {
        case 1:
            cmp = (direction == 1) ? cmp_full_name_asc : cmp_full_name_desc;
            break;
        case 2:
            cmp = (direction == 1) ? cmp_number_asc : cmp_number_desc;
            break;
        case 3:
            cmp = (direction == 1) ? cmp_time_asc : cmp_time_desc;
            break;
        default:
            return;
    }

    qsort(arr->ptr, arr->size, sizeof(Sub), cmp);
}
