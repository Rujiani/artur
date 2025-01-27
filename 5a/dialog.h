#ifndef DIALOG_H_
#define DIALOG_H_

#include "array.h"

// Main menu
int menu(int *choice);

// Read array
int array_input(Array *arr);

// Write array
int array_output(const Array *arr);

// Sort array
int array_sort(Array *arr);

#endif
