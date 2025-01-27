#ifndef SUBSCRIBER_H
#define SUBSCRIBER_H

// Subscriber structure
typedef struct subscriber {
    char *full_name;
    char *number;
    int last_call_time;
} Sub;

// Print a single subscriber
void sub_print(const Sub *s);

// Comparators for sorting
int sub_cmp_full_name_asc(const Sub *s1, const Sub *s2);
int sub_cmp_full_name_desc(const Sub *s1, const Sub *s2);
int sub_cmp_number_asc(const Sub *s1, const Sub *s2);
int sub_cmp_number_desc(const Sub *s1, const Sub *s2);
int sub_cmp_last_call_time_asc(const Sub *s1, const Sub *s2);
int sub_cmp_last_call_time_desc(const Sub *s1, const Sub *s2);

#endif
