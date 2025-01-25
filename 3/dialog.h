#ifndef DIALOG_H_
#define DIALOG_H_
#include "array.h"


int menu();
int array_initialization(Array *);
int array_change_memory_size(Array *);
int array_insert_el(Array *);
int array_delete_el(Array *);
void array_subsequence_stuff(Array *);
void array_print(Array *);

#endif