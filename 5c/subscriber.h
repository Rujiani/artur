#ifndef SUBSCRIBER_H
#define SUBSCRIBER_H

typedef struct subscriber {
    char *full_name;     // dynamically allocated
    char *number;        // dynamically allocated
    int last_call_time;
} Sub;

// Comparators for Sub, but with (const void*, const void*) signature
int cmp_full_name_asc(const void *a, const void *b);
int cmp_full_name_desc(const void *a, const void *b);
int cmp_number_asc(const void *a, const void *b);
int cmp_number_desc(const void *a, const void *b);
int cmp_time_asc(const void *a, const void *b);
int cmp_time_desc(const void *a, const void *b);

// Free dynamic fields of one subscriber
void sub_free(Sub *s);

#endif
