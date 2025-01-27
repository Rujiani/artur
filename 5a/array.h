#ifndef ARRAY_H
#define ARRAY_H

#include "subscriber.h"

// Structure for an array of Sub
typedef struct {
    Sub *ptr;
    int size;
} Array;

// Read array from stdin
int array_read_stdin(Array *arr);

// Read array from text file
int array_read_text(Array *arr, const char *filename);

// Read array from binary file
int array_read_bin (Array *arr, const char *filename);

// Write array to stdout
int array_write_stdout(const Array *arr);

// Write array to text file
int array_write_text(const Array *arr, const char *filename);

// Write array to binary file
int array_write_bin (const Array *arr, const char *filename);

// Sort array with qsort, field = 1..3, direction = 1..2
void array_qsort(Array *arr, int field, int direction);

#endif
