#ifndef ARRAY_H_
#define ARRAY_H_
typedef struct array{
    int *ptr, size, reserved;
} Array;

int create_new_array(Array *, int);
int change_size(Array *, int);
int add_element(Array *, int);
int delete_element(Array *, int);
void subsequence_stuff(Array *);
void print(Array *);

#endif