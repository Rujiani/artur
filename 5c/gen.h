#ifndef GEN_H
#define GEN_H

#include "subscriber.h"

// Generate one random subscriber
Sub generate_random_sub();

// Generate a random array of subscribers (size elements)
Sub* generate_sub_array(int size);

// Free an entire array of subscribers
void free_sub_array(Sub *arr, int size);

#endif
