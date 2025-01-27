#ifndef SORT_H
#define SORT_H

#include "subscriber.h"
#include <stddef.h>

// Comparators for Sub, but with (const void*, const void*) signature
int cmp_full_name_asc(const void *a, const void *b);
int cmp_full_name_desc(const void *a, const void *b);
int cmp_number_asc(const void *a, const void *b);
int cmp_number_desc(const void *a, const void *b);
int cmp_time_asc(const void *a, const void *b);
int cmp_time_desc(const void *a, const void *b);

// Select comparator by field/direction
int (*select_cmp(int field, int direction))(const void*, const void*);

// Bubble sort
void bubble_sort(void *base, size_t n, size_t size, int (*cmp)(const void*, const void*));

// Pair insertion sort
void pair_insertion_sort(void *base, size_t n, size_t size, int (*cmp)(const void*, const void*));

// Sort Sub array with chosen algorithm
// algo: 1-qsort, 2-bubble, 3-pair insertion
void sort_sub_array(Sub *arr, int size, int algo, int field, int direction);

#endif