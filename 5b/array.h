#ifndef ARRAY_H
#define ARRAY_H

#include "subscriber.h"

typedef struct {
    Sub *ptr;
    int size;
} Array;

// Existing input/output functions...
int array_read_stdin(Array *arr);
int array_read_text(Array *arr, const char *filename);
int array_read_bin (Array *arr, const char *filename);

int array_write_stdout(const Array *arr);
int array_write_text(const Array *arr, const char *filename);
int array_write_bin (const Array *arr, const char *filename);

// Existing qsort-based sorting
void array_qsort(Array *arr, int field, int direction);

void array_bubble_sort(Array *arr, int field, int direction);
void array_pair_insertion_sort(Array *arr, int field, int direction);

#endif
