#include "array.h"
#include "subscriber.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Frees old data
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
    if (scanf("%d", &n) != 1 || n <= 0) return -1;
    getchar(); 

    free_array_data(arr);
    arr->ptr = (Sub*)malloc(n * sizeof(Sub));
    if (!arr->ptr) return -1;
    arr->size = n;

    for (int i = 0; i < n; i++) {
        char buf_name[256];
        char buf_num[256];
        int time_val;

        printf("Subscriber %d:\n", i + 1);
        printf("  Full name: ");
        if (scanf(" %[^\n]", buf_name) != 1) return -1;
        getchar();

        printf("  Number: ");
        if (scanf(" %[^\n]", buf_num) != 1) return -1;
        getchar();

        printf("  Last call time: ");
        if (scanf("%d", &time_val) != 1) return -1;
        getchar();

        arr->ptr[i].full_name = strdup(buf_name);
        arr->ptr[i].number = strdup(buf_num);
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

    // Read the number of subscribers
    int n;
    if (fscanf(f, "%d", &n) != 1 || n <= 0) {
        fclose(f);
        return -1;
    }
    // Consume the leftover '\n'
    fgetc(f);

    // Clear old data if any
    free_array_data(arr); // Make sure you have a function that frees arr->ptr, etc.

    // Allocate new array
    arr->ptr = (Sub*)malloc(n * sizeof(Sub));
    if (!arr->ptr) {
        fclose(f);
        return -1;
    }
    arr->size = n;

    for (int i = 0; i < n; i++) {
        // Read one line
        char line[1024];
        if (!fgets(line, sizeof(line), f)) {
            fclose(f);
            return -1;
        }

        // Remove trailing newline if present
        char *nl = strchr(line, '\n');
        if (nl) *nl = '\0';

        // Tokenize the line by spaces or tabs
        char *tokens[256];
        int nt = 0;
        char *p = strtok(line, " \t");
        while (p && nt < 256) {
            tokens[nt++] = p;
            p = strtok(NULL, " \t");
        }

        // We need at least 3 tokens: [multi-word FIO ...] [number] [time]
        if (nt < 3) {
            fclose(f);
            return -1;
        }

        // The last token is the time (int)
        int time_val = atoi(tokens[nt - 1]);

        // The second-to-last token is the number
        char *phone = tokens[nt - 2];

        // Everything before that is the multi-word full name
        int len_name = 0;
        for (int k = 0; k < nt - 2; k++) {
            len_name += (int)strlen(tokens[k]) + 1; 
        }
        char *full_name = (char*)malloc(len_name + 1);
        if (!full_name) {
            fclose(f);
            return -1;
        }
        full_name[0] = '\0';

        // Join tokens[0..nt-3] into one string for FIO
        for (int k = 0; k < nt - 2; k++) {
            strcat(full_name, tokens[k]);
            if (k < nt - 3) strcat(full_name, " ");
        }

        // Save data in arr->ptr[i]
        arr->ptr[i].full_name = full_name;
        arr->ptr[i].number = strdup(phone);
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

        int len_num;
        if (fread(&len_num, sizeof(int), 1, f) != 1) {
            free(fullname);
            fclose(f);
            return -1;
        }
        char *number = (char*)malloc(len_num + 1);
        if (!number) {
            free(fullname);
            fclose(f);
            return -1;
        }
        if (fread(number, 1, len_num, f) != (size_t)len_num) {
            free(fullname);
            free(number);
            fclose(f);
            return -1;
        }
        number[len_num] = '\0';

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

// Write to stdout
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

// Write to text file
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

// Write to binary file
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
        int len_num = (int)strlen(arr->ptr[i].number);
        if (fwrite(&len_num, sizeof(int), 1, f) != 1) {
            fclose(f);
            return -1;
        }
        if (fwrite(arr->ptr[i].number, 1, len_num, f) != (size_t)len_num) {
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

// Comparators for qsort or other sorts
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

static int (*select_cmp(int field, int dir))(const void*, const void*) {
    if (field == 1) return (dir == 1) ? cmp_full_name_asc : cmp_full_name_desc;
    if (field == 2) return (dir == 1) ? cmp_number_asc    : cmp_number_desc;
    if (field == 3) return (dir == 1) ? cmp_time_asc      : cmp_time_desc;
    return NULL;
}

// qsort-based sort
void array_qsort(Array *arr, int field, int direction) {
    if (!arr || arr->size <= 1) return;
    int (*cmp)(const void*, const void*) = select_cmp(field, direction);
    if (!cmp) return;
    qsort(arr->ptr, arr->size, sizeof(Sub), cmp);
}

// Generic bubble
static void bubble_sort(void *base, size_t n, size_t size, 
                        int (*cmp)(const void*, const void*)) {
    char *a = (char*)base;
    for (size_t i = 0; i < n - 1; i++) {
        for (size_t j = 0; j < n - 1 - i; j++) {
            void *p1 = a + j*size;
            void *p2 = a + (j+1)*size;
            if (cmp(p1, p2) > 0) {
                char temp[256];
                memcpy(temp, p1, size);
                memcpy(p1, p2, size);
                memcpy(p2, temp, size);
            }
        }
    }
}

// Bubble
void array_bubble_sort(Array *arr, int field, int direction) {
    if (!arr || arr->size <= 1) return;
    int (*cmp)(const void*, const void*) = select_cmp(field, direction);
    if (!cmp) return;
    bubble_sort(arr->ptr, arr->size, sizeof(Sub), cmp);
}

// Pair insertion (internal) 256 character limit :(
static void pair_insertion_sort(void *base, size_t n, size_t size,
                                int (*cmp)(const void*, const void*)) {
    // We'll treat the array as a char-buffer
    char *a = (char*)base;
    size_t i = 0;

    // Process two elements at a time
    for (; i + 1 < n; i += 2) {
        // Read two elements X and Y
        char X[256], Y[256];
        memcpy(X, a + i * size,     size);
        memcpy(Y, a + (i + 1) * size, size);

        // If X < Y, swap them => after this, X >= Y
        if (cmp(X, Y) < 0) {
            char tmp[256];
            memcpy(tmp, X, size);
            memcpy(X, Y, size);
            memcpy(Y, tmp, size);
        }

        // Insert X
        int j = (int)i - 1;
        while (j >= 0 && cmp(a + j * size, X) > 0) {
            memcpy(a + (j + 2) * size, a + j * size, size);
            j--;
        }
        memcpy(a + (j + 2) * size, X, size);

        // Insert Y
        while (j >= 0 && cmp(a + j * size, Y) > 0) {
            memcpy(a + (j + 1) * size, a + j * size, size);
            j--;
        }
        memcpy(a + (j + 1) * size, Y, size);
    }

    // If the array length is odd, we have one last element to insert
    if (i < n) {
        char last[256];
        memcpy(last, a + i * size, size);
        int j = (int)i - 1;
        while (j >= 0 && cmp(a + j * size, last) > 0) {
            memcpy(a + (j + 1) * size, a + j * size, size);
            j--;
        }
        memcpy(a + (j + 1) * size, last, size);
    }
}

// Pair insertion
void array_pair_insertion_sort(Array *arr, int field, int direction) {
    if (!arr || arr->size <= 1) return;
    int (*cmp)(const void*, const void*) = select_cmp(field, direction);
    if (!cmp) return;
    pair_insertion_sort(arr->ptr, arr->size, sizeof(Sub), cmp);
}
